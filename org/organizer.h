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

    void createTable(const std::string & query) const;

    void insert(const boost::filesystem::path & p) const;

    const std::string supprimerGuillemets(const QString & Qstr);

    MD5Key *md5(const char* filename);

    void searchDouble(void);

    void searchBySize(const uint64_t size);

    void setRacine(const std::string &);
    const std::string & getRacine() const;

    void searchEmpty();

    bool isUpdate(const boost::filesystem::path & p) const;
};

#endif // ORGANIZER_H
