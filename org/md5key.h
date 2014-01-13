#ifndef MD5KEY_H
#define MD5KEY_H

#include <string>

class MD5Key
{
    unsigned char md5[16];
public:
    MD5Key(const unsigned char*);
    const std::string toString() const;
    friend bool operator<(const MD5Key&k1, const MD5Key&k2);
    friend bool operator== (const MD5Key&k1, const MD5Key&k2);
    friend bool operator!= (const MD5Key&k1, const MD5Key&k2);
};

bool operator< (const MD5Key&k1, const MD5Key&k2);
bool operator== (const MD5Key&k1, const MD5Key&k2);
bool operator!= (const MD5Key&k1, const MD5Key&k2);
std::ostream& operator<< (std::ostream& os, const MD5Key);

#endif // MD5KEY_H
