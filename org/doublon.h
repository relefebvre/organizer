#ifndef DOUBLON_H
#define DOUBLON_H

/**
 *\file doublon.h
 *\author Ducros & Lefebvre
 *\date 21 Janvier 2014
 *\brief Définit les doublons
 */

#include <string>
#include "md5key.h"

/**
 * @brief Classe représantant le doublon
 *\class Doublon
 */

class Doublon
{
    std::string path ; /**< Chemin absolu du fichier*/
    MD5Key *md5; /**< Objet représentant la clé MD5 du fichier*/

public:

    /**
     * @brief Constructeur de la classe Doublon
     * @param[in] path : chemin absolu du fichier
     */
    Doublon(const std::string &path);

    /**
     * @brief Setteur de la clé MD5
     * @param[in] md5 : tableau correspondant à la clé MD5 du fichier
     */
    void setKey(const unsigned char* md5);

    /**
     * @brief Getteur de la clé MD5
     * @return Pointeur sur l'objet représentant la clé MD5
     */
    MD5Key* getKey() const ;

    /**
     * @brief Getteur du chemin du fichier
     * @return Pointeur sur le tableau contenant le chemin du fichier
     */
    const char *getPath() const;

    /**
     * @brief Destructeur de la classe Doublon
     */
    ~Doublon() ;
};



#endif // DOUBLON_H
