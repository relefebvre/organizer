#include "doublon.h"
#include <string>
#include <string.h>
#include <sstream>
#include <iostream>

Doublon::Doublon(std::string path)
    :path(path)
{}

void Doublon::setKey(const unsigned char * md5)
{
    this->md5 = new MD5Key(md5);
}


MD5Key *Doublon::getKey() const
{
    return md5 ;
}

const char *Doublon::getPath() const
{
    return path.c_str();
}

Doublon::~Doublon()
{
    delete this->md5;
}
