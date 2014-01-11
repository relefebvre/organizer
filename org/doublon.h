#ifndef DOUBLON_H
#define DOUBLON_H

#include <string>
#include <stdint.h>

class Doublon
{
    std::string path ;
    unsigned char md5[16];

public:
    Doublon(std::string path);
    Doublon(const unsigned char*key);
    friend bool operator<(const Doublon&k1, const Doublon&k2);
    friend bool operator== (const Doublon&k1, const Doublon&k2);
    friend bool operator!= (const Doublon&k1, const Doublon&k2);
    const std::string toString() const;
    void setKey(unsigned char*);
    const unsigned char* getKey() const ;
    const char *getPath() const;
    ~Doublon() ;
};

bool operator< (const Doublon&d1, const Doublon&d2);
bool operator== (const Doublon&d1, const Doublon&d2);
bool operator!= (const Doublon&d1, const Doublon&d2);
std::ostream& operator<< (std::ostream& os, const Doublon);

#endif // DOUBLON_H
