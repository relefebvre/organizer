#include "doublon.h"
#include <string>
#include <string.h>

Doublon::Doublon(int size, std::string path, unsigned char *md5)
{
    this->size = size ;
    this->path= path ;
    this->md5 = new unsigned char[16] ;
    memcpy(this->md5,md5,sizeof(unsigned char)*16) ;

}

Doublon::~Doublon()
{
    delete this->md5 ;

}
