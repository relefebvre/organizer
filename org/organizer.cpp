#include "organizer.h"
#include <QtSql>
#include <QSqlDatabase>
#include <sstream>
#include <stdarg.h>
#include <tomcrypt.h>
#include <set>

Organizer::Organizer()
{
    if (!createDB())
    {
        perror("Open DB");
        exit(errno);
    }

    createTable("CREATE TABLE fic(size integer,path varchar(1000) UNIQUE);");

    createTable("CREATE TABLE dir(empty bool,path varchar(1000) UNIQUE);");
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

//    std::cout<<p<<std::endl;

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
        //system("ls -la | wc -l")
        query.prepare("INSERT INTO dir(empty, path)"
                      "VALUES (:empty, :path);");
        query.bindValue(":empty",boost::filesystem::is_empty(p));
        query.bindValue(":path", p.c_str());
    }
    query.exec();
}


std::string Organizer::supprimerGuillemets(QString Qstr)
{
    std::string str=Qstr.toStdString();
    str.erase(remove(str.begin(), str.end(), '"'), str.end());
    return str;
}


unsigned char* Organizer::md5(const char* filename)
{
    hash_state md;
    unsigned char *out = new unsigned char[16];
    char buf[4096];
    unsigned int nbLu=0;

    FILE *fic;
    fic = fopen(filename,"r");
    if (fic == 0)
    {
        perror("fopen");
        exit(errno);
    }

    md5_init(&md);

    while (nbLu != boost::filesystem::file_size(filename))
    {
        unsigned int tmp;
        tmp = fread(buf,sizeof(char),4096,fic);
        md5_process(&md, (const unsigned char*)buf, tmp);
        nbLu += tmp;
    }

    md5_done(&md, out);

    fclose(fic);

    return out;
}

void Organizer::searchDouble()
{
    QSqlQuery query;

    query.exec("SELECT Count(*), size FROM fic GROUP BY size HAVING Count(*) > 1;");

    while (query.next())
        searchBySize(query.value(1).toULongLong());

    for( std::map<uint64_t,std::list<boost::filesystem::path> >::iterator it=doublons.begin() ; it!=doublons.end() ; )
    {
        if (it->second.size() == 2)
        {
            if (memcmp(md5(it->second.front().string().c_str()),md5(it->second.back().string().c_str()),sizeof(char)*16) != 0)
                doublons.erase(it);
        }
        else
        {
            unsigned cpt=0;
            std::set<unsigned char*> md5Sum;
            std::pair<std::set<unsigned char*>::iterator,bool> ret;
            for (std::list<boost::filesystem::path>::const_iterator itp=it->second.begin() ; itp!=it->second.end() ; ++itp)
            {
                ret = md5Sum.insert(md5(itp->string().c_str()));
                if (!ret.second)
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

    query.prepare("SELECT path FROM fic WHERE size=:size");
    std::stringstream Ssize;
    Ssize << size;
    query.bindValue(":size",Ssize.str().c_str());
    query.exec();

    while (query.next()) {
        std::string ph =supprimerGuillemets(query.value(0).toString());
        doublons[size].push_back((boost::filesystem::path)ph);
    }
}

void Organizer::afficherDoublons()
{
    for( std::map<uint64_t,std::list<boost::filesystem::path> >::const_iterator it=doublons.begin() ; it!=doublons.end() ; ++it)
    {
        std::cout<<"Taille : "<<it->first<<std::endl;
        for (std::list<boost::filesystem::path>::const_iterator itp=it->second.begin() ; itp!=it->second.end() ; ++itp)
            std::cout<<itp->filename()<<std::endl;
    }
}
