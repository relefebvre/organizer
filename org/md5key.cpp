#include "md5key.h"
#include <string.h>
#include <sstream>

MD5Key::MD5Key(const unsigned char * md5)
{
    memcpy(this->md5,md5,sizeof(unsigned char)*16);
}

const std::string MD5Key::toString() const
{
    std::stringstream tmp;
    tmp.setf(std::ios_base::hex) ;
    tmp << md5;
    return std::string(tmp.str());
}

bool operator<(const MD5Key &k1, const MD5Key &k2)
{
    if(memcmp(k1.md5, k2.md5, sizeof(unsigned char)*16) < 0)
        return true ;
    return false ;
}

bool operator ==(const MD5Key &k1, const MD5Key &k2)
{
    if(memcmp(k1.md5, k2.md5, sizeof(unsigned char)*16) == 0)
        return true ;
    return false ;
}

bool operator !=(const MD5Key &k1, const MD5Key &k2)
{
    if(memcmp(k1.md5, k2.md5, sizeof(unsigned char)*16) == 0)
        return false ;
    return true ;
}

std::ostream &operator<<(std::ostream &os, const MD5Key k1)
{
    return os << k1.toString();
}
