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

void Organizer::createTable(std::string command) const
{
    QSqlQuery query;
    query.exec(command.c_str());
}

void Organizer::insert(boost::filesystem::path p) const
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


std::string Organizer::supprimerGuillemets(QString Qstr)
{
    std::string str=Qstr.toStdString();
    str.erase(remove(str.begin(), str.end(), '"'), str.end());
    return str;
}


MD5Key* Organizer::md5(const char* filename)
{
    hash_state md;
    unsigned char *out = new unsigned char[16];
    unsigned char buf[4096];
    unsigned int nbLu=0;

    MD5Key *md5;

    QSqlQuery query;

    query.prepare("SELECT md5 FROM fic WHERE path=:path");
    query.bindValue(":path",filename);
    query.exec();

    if (query.next() && query.value(0).toString().length() > 0)
        memcpy((unsigned char*)out,query.value(0).toString().toStdString().c_str(),sizeof(unsigned char)*16);
    else
    {
        int fd;
        fd = open(filename,O_RDONLY);
        if (fd == -1)
        {
            perror("open");
            exit(errno);
        }

        md5_init(&md);


        while (nbLu != boost::filesystem::file_size(filename))
        {
            unsigned int tmp;
            tmp = read(fd,buf,sizeof(buf));
            md5_process(&md,buf, tmp);
            nbLu += tmp;
        }

        md5_done(&md, out);

        close(fd);
    }

    md5 = new MD5Key(out);

    query.prepare("UPDATE fic SET md5=:md5 WHERE path=:path");
    query.bindValue(":md5",md5->toString().c_str());
    query.bindValue(":path",filename);
    query.exec();

    return md5;
}

void Organizer::searchDouble()
{


    QSqlQuery query;

    query.exec("SELECT Count(*), size FROM fic GROUP BY size HAVING Count(*) > 1;");

    while (query.next())
        searchBySize(query.value(1).toULongLong());

    unsigned cpt=0;

    for( std::map<uint64_t,std::list<boost::filesystem::path> >::iterator it=doublons.begin() ; it!=doublons.end() ; )
    {
        if (it->second.size() == 2)
        {
            if (*md5(it->second.front().string().c_str()) != *md5(it->second.back().string().c_str()))
                doublons.erase(it);
        }
        else
        {
            std::set<MD5Key> md5Sum;
            std::pair<std::set<MD5Key>::const_iterator,bool> ret;

            for (std::list<boost::filesystem::path>::const_iterator itp=it->second.begin() ; itp!=it->second.end() ; ++itp)
            {
                ret = md5Sum.insert(*md5(itp->string().c_str()));

                if (ret.second == false)
                    ++cpt;
            }
            if (cpt == 0)
                doublons.erase((it));
        }
        ++it;
    }

}

void Organizer::searchBySize(uint64_t size)
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
        doublons[size].push_back((boost::filesystem::path)ph);
    }
}


void Organizer::setRacine(std::string s)
{
    std::cout<<s<<std::endl;
    racine = s;
}

std::string Organizer::getRacine()
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

bool Organizer::isUpdate(boost::filesystem::path p) const
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

