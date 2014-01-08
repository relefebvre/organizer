#ifndef ORGANIZER_H
#define ORGANIZER_H

#include <string>
#include <stdint.h>
#include <boost/filesystem.hpp>
#include <QString>
#include <map>
#include <list>
#include "md5key.h"

class Organizer
{

protected:
    std::map<uint64_t,std::list<boost::filesystem::path> > doublons;
    std::list<boost::filesystem::path> emptyDir;
    std::string racine;

public:
    Organizer();

    bool createDB() const;

    void createTable(std::string query) const;

    void insert(boost::filesystem::path p) const;

    std::string supprimerGuillemets(QString Qstr);

    MD5Key *md5(const char* filename);

    void searchDouble(void);

    void searchBySize(uint64_t size);

    void setRacine(std::string);
    std::string getRacine();

    void searchEmpty();

    bool isUpdate(boost::filesystem::path p) const;

    void setStatus(std::string s);
};

#endif // ORGANIZER_H
