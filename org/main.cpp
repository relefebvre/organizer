#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <map>
#include <stdint.h>
#include <QtSql>
#include <QSqlDatabase>
#include <sstream>
#include <tomcrypt.h>
#include <list>
#include <algorithm>


using namespace boost::filesystem;
using namespace std;

string supprimerGuillemets(QString Qstr)
{
    string str=Qstr.toStdString();
    str.erase(remove(str.begin(), str.end(), '"'), str.end());
    return str;
}

unsigned char* md5(const char* filename)
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

    while (nbLu != file_size(filename))
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

int main(int argc, char* argv[])
{
   std::list<path> doublons;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db");
    bool ok = db.open();
    std::cout<<"Ouverture db : "<<ok<<std::endl;

    QSqlQuery query;

    std::cout<<query.exec("CREATE TABLE fic(size integer,path varchar(1000) UNIQUE);")<<std::endl;
    std::cout<<query.exec("CREATE TABLE dir(empty bool,path varchar(1000) UNIQUE);")<<std::endl;

    for ( recursive_directory_iterator end, dir(argv[1]);
          dir != end; ++dir ) {
        path ph = *dir;

        if (ph.filename().c_str()[0] == '.')
        {
            dir.no_push();
            continue;
        }

        std::string path = ph.string();

        if (is_regular_file(*dir))
        {
            uint64_t size = file_size(*dir);
            std::stringstream Ssize;
            Ssize << size;
            query.prepare("INSERT INTO fic(size, path)"
                          "VALUES (:size, :path);");
            query.bindValue(":size", Ssize.str().c_str());
            query.bindValue(":path", path.c_str());
        }
        if (is_directory(*dir))
        {
            query.prepare("INSERT INTO dir(empty, path)"
                          "VALUES (:empty, :path);");
            query.bindValue(":empty",is_empty(ph));
            query.bindValue(":path", path.c_str());
        }
        query.exec();
    }

/*
    query.prepare("SELECT path FROM fic WHERE size=:size");
    std::stringstream Ssize;
    Ssize << file_size(argv[2]);
    query.bindValue(":size",Ssize.str().c_str());
    query.exec();

    while (query.next()) {
        string ph =supprimerGuillemets(query.value(0).toString());
        cout << ph <<endl;
        if (memcmp(md5(ph.c_str()),md5(argv[2]),sizeof(md5(argv[2]))) == 0)
        {
            cout<<md5(ph.c_str())<<" :"<<md5(argv[2])<<endl;
            doublons.push_back((path)ph);
            cout<<"Ajout doublon"<<endl;
        }
        }
*/

    query.exec("SELECT Count(*), path FROM fic GROUP BY size HAVING Count(*) > 1;");
    while (query.next()) {
            QString name = query.value(1).toString();
            qDebug() << name;
        }
   /*
    std::cout << "Doublons taille : " << std::endl;
    for (list<path>::const_iterator it=doublons.begin() ; it!= doublons.end() ; ++it)
        cout<<*it<<endl;
*/

    return 0;
}

