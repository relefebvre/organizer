#ifndef MD5KEY_H
#define MD5KEY_H

#include <iostream>
#include <string>
#include <ostream>

class MD5Key
{
    unsigned char key[16];


public:
    MD5Key(const unsigned char*key);
    friend bool operator<(const MD5Key&k1, const MD5Key&k2);
    friend bool operator== (const MD5Key&k1, const MD5Key&k2);
    friend bool operator!= (const MD5Key&k1, const MD5Key&k2);
    std::string toString() const;
    const unsigned char* getKey() const ;
};

bool operator< (const MD5Key&k1, const MD5Key&k2);
bool operator== (const MD5Key&k1, const MD5Key&k2);
bool operator!= (const MD5Key&k1, const MD5Key&k2);
std::ostream& operator<< (std::ostream& os, const MD5Key);

#endif // MD5KEY_H
