#ifndef DOUBLON_H
#define DOUBLON_H

#include <string>
#include <stdint.h>
#include "md5key.h"

class Doublon
{
    std::string path ;
    MD5Key *md5;

public:
    Doublon(std::string path);

    void setKey(const unsigned char*);
    MD5Key* getKey() const ;

    const char *getPath() const;

    ~Doublon() ;
};



#endif // DOUBLON_H
