#include "md5key.h"
#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <fstream>

MD5Key::MD5Key(const unsigned char * key)
{
    memcpy(this->key, key, sizeof(unsigned char)*16);
}

bool operator<(const MD5Key &k1, const MD5Key &k2)
{
    if(memcmp(k1.getKey(), k2.getKey(), sizeof(unsigned char)*16) < 0)
        return true ;
    return false ;
}

std::string MD5Key::toString() const
{
    std::stringstream tmp;
    tmp.setf(std::ios_base::hex) ;
    tmp << key;
    return std::string(tmp.str());
}

const unsigned char *MD5Key::getKey() const
{
    return key ;
}


std::ostream &operator<<(std::ostream &os, const MD5Key k1)
{
    return os << k1.toString();
}
