#ifndef DOUBLON_H
#define DOUBLON_H

#include <string>

class Doublon
{
    int size ;
    std::string path ;
    unsigned char* md5;

public:
    Doublon(int size, std::string path, unsigned char* md5);
    Doublon() {}
    ~Doublon() ;
};

#endif // DOUBLON_H
