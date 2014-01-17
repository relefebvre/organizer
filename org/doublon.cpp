#include "doublon.h"
#include <string>

/**
 *\file doublon.cpp
 *\author Ducros & Lefebvre
 *\date 21 Janvier 2014
 *\brief Définit les doublons
 */

Doublon::Doublon(const std::string& path)
    :path(path)
{}

Doublon::~Doublon()
{
    delete this->md5;
}
