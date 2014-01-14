/**
 *\file doublon.cpp
 *\author Ducros & Lefebvre
 *\date 21 Janvier 2014
 *\brief Définit les doublons
 */

#include "doublon.h"
#include <string>

Doublon::Doublon(const std::string& path)
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
