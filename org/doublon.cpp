#include "doublon.h"
#include <string>
#include <string.h>
#include <sstream>
#include <iostream>

Doublon::Doublon(std::string path)
    :path(path)
{}

bool operator<(const Doublon &k1, const Doublon &k2)
{
    if(memcmp(k1.getKey(), k2.getKey(), sizeof(unsigned char)*16) < 0)
        return true ;
    return false ;
}

bool operator ==(const Doublon &k1, const Doublon &k2)
{
    if(memcmp(k1.getKey(), k2.getKey(), sizeof(unsigned char)*16) == 0)
        return true ;
    return false ;
}

bool operator !=(const Doublon &k1, const Doublon &k2)
{
    if(memcmp(k1.getKey(), k2.getKey(), sizeof(unsigned char)*16) == 0)
        return false ;
    return true ;
}

const std::string Doublon::toString() const
{
    std::stringstream tmp;
    tmp.setf(std::ios_base::hex) ;
    tmp << md5;
    return std::string(tmp.str());
}

void Doublon::setKey(unsigned char *md5)
{
    memcpy(this->md5,md5,sizeof(unsigned char)*16) ;
}

const unsigned char *Doublon::getKey() const
{
    return md5 ;
}

const char *Doublon::getPath() const
{
    return path.c_str();
}


std::ostream &operator<<(std::ostream &os, const Doublon k1)
{
    return os << k1.toString();
}

Doublon::~Doublon()
{
    delete this->md5 ;

}
