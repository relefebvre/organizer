#include "organizer.h"
#include <QtSql>
#include <QSqlDatabase>
#include <sstream>
#include <stdarg.h>
#include <tomcrypt.h>
#include <set>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

Organizer::Organizer()
{
    if (!createDB())
    {
        perror("Open DB");
        exit(errno);
    }

    createTable("CREATE TABLE fic(size integer,path varchar(1000) UNIQUE, md5 varchar(16));");

    createTable("CREATE TABLE dir(empty bool,path varchar(1000) UNIQUE, modif datetime);");
}

bool Organizer::createDB() const
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db");
    return db.open();
}

void Organizer::createTable(const std::string &command) const
{
    QSqlQuery query;
    query.exec(command.c_str());
}

void Organizer::insert(const boost::filesystem::path &p) const
{
    QSqlQuery query;

    if (boost::filesystem::is_regular_file(p))
    {
        uint64_t size = boost::filesystem::file_size(p);
        std::stringstream Ssize;
        Ssize << size;
        query.prepare("INSERT INTO fic(size, path)"
                      "VALUES (:size, :path);");
        query.bindValue(":size", Ssize.str().c_str());
        query.bindValue(":path", p.c_str());
    }
    if (boost::filesystem::is_directory(p))
    {
        struct stat info;
        if (stat(p.c_str(),&info) == -1)
        {
            perror("stat");
            exit(errno);
        }

        query.prepare("INSERT INTO dir(empty, path, modif)"
                      "VALUES (:empty, :path, :modif);");
        query.bindValue(":empty",boost::filesystem::is_empty(p));
        query.bindValue(":path", p.c_str());
        query.bindValue(":modif", QString::number(info.st_mtime));
    }
    query.exec();
}


const std::string Organizer::supprimerGuillemets(const QString &Qstr)
{
    std::string str=Qstr.toStdString();
    str.erase(remove(str.begin(), str.end(), '"'), str.end());
    return str;
}


void Organizer::md5(Doublon *d)
{
    hash_state md;
    unsigned char *out = new unsigned char[16];
    unsigned char buf[4096];
    unsigned int nbLu=0;

    QSqlQuery query;

    query.prepare("SELECT md5 FROM fic WHERE path=:path");
    query.bindValue(":path",d->getPath());
    query.exec();

    bool update = true;

    if (query.next() && query.value(0).toString().length() > 0)
    {
        update= false;
        memcpy((unsigned char*)out,query.value(0).toString().toStdString().c_str(),sizeof(unsigned char)*16);
    }
    else
    {
        int fd;
        fd = open(d->getPath(),O_RDONLY);
        if (fd == -1)
        {
            perror("open");
            exit(errno);
        }

        md5_init(&md);


        while (nbLu != boost::filesystem::file_size(d->getPath()))
        {
            unsigned int tmp;
            tmp = read(fd,buf,sizeof(buf));
            md5_process(&md,buf, tmp);
            nbLu += tmp;
        }

        md5_done(&md, out);

        close(fd);
    }

    d->setKey(out);

    if (update)
    {
        query.prepare("UPDATE fic SET md5=:md5 WHERE path=:path");
        query.bindValue(":md5",d->toString().c_str());
        query.bindValue(":path",d->getPath());
        query.exec();
    }
}

void Organizer::searchDouble()
{
    QSqlQuery query;

    query.exec("SELECT Count(*), size FROM fic GROUP BY size HAVING Count(*) > 1;");

    while (query.next())
        searchBySize(query.value(1).toULongLong());

    for (std::multiset<Doublon*>::const_iterator itd=doublonSize.begin() ; itd!=doublonSize.end() ; ++itd)
    {
        std::pair<std::multiset<Doublon*>::iterator,std::multiset<Doublon*>::iterator> ret = doublonSize.equal_range(*itd);

        for (std::multiset<Doublon*>::iterator itr = ret.first ; itr != ret.second ; ++itr)
        {
            std::string ph = (*itr)->getPath();
            doublons[(*itd)->toString()].push_back(boost::filesystem::path(ph));
        }
        doublonSize.erase(ret.first,ret.second);
    }
}

void Organizer::searchBySize(const uint64_t size)
{
    QSqlQuery query;

    query.prepare("SELECT path FROM fic WHERE size=:size AND path LIKE :path");
    std::stringstream Ssize;
    Ssize << size;
    query.bindValue(":size",Ssize.str().c_str());
    std::string s = getRacine()+"%";
    query.bindValue(":path",s.c_str());
    query.exec();

    while (query.next()) {
        std::string ph =supprimerGuillemets(query.value(0).toString());
        Doublon *tmp = new Doublon(ph);
        md5(tmp);
        doublonSize.insert(tmp);
    }
}


void Organizer::setRacine(const std::string &s)
{
    racine = s;
}

const std::string &Organizer::getRacine() const
{
    return racine;
}

void Organizer::searchEmpty()
{
    QSqlQuery query;

    query.prepare("SELECT path FROM dir WHERE empty=\"true\" AND path LIKE :path");
    std::string s = getRacine()+"%";
    query.bindValue(":path",s.c_str());
    query.exec();

    while (query.next()) {
        std::string ph =supprimerGuillemets(query.value(0).toString());
        emptyDir.push_back((boost::filesystem::path)ph);
    }
}

bool Organizer::isUpdate(const boost::filesystem::path &p) const
{
    QSqlQuery query;
    query.prepare("SELECT modif FROM dir WHERE path=:path");
    query.bindValue(":path",p.c_str());
    query.exec();

    struct stat info;
    if (stat(p.c_str(),&info) == -1)
    {
        perror("stat");
        exit(errno);
    }

    while(query.next())
    {
        if (QDateTime::fromTime_t(info.st_mtime) > query.value(0).toDateTime())
            return true;
        else
            return false;
    }

    return false;
}

