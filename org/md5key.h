#ifndef MD5KEY_H
#define MD5KEY_H

/**
 *\file md5key.h
 *\author Ducros & Lefebvre
 *\date 21 Janvier 2014
 *\brief Définit les clé MD5 des doublons
 */

#include <string>


/**
 * @brief The MD5Key class
 *\class MD5Key
 *\brief Classe représentant la clé MD5
 */


class MD5Key
{
    unsigned char md5[16]; /**< Tableau contenant la clé MD5*/
public:

    /**
     * @brief MD5Key
     *\brief Constructeur de la classe MD5Key
     *\param[in] path : chemin aboslu du fichier
     */
    MD5Key(const unsigned char*);

    /**
     * @brief toString
     * @return
     *\brief Transforme la clé MD5 en string
     *\return String correspondant à la clé MD5
     */
    const std::string toString() const;

    /**
     * @brief operator <
     * @param k1
     * @param k2
     * @return
     *\brief Surchagre de l'opérateur "inférieur"
     *\param[in] k1 : MD5Key servant à la comparaison
     *\param[in] k2 : MD5Key servant à la comparaison
     *\return true si l'objet k1 est plus petit que l'objet k2 false sinon
     */
    friend bool operator<(const MD5Key&k1, const MD5Key&k2);

    /**
     * @brief operator ==
     * @param k1
     * @param k2
     * @return
     *\brief Surchagre de l'opérateur "égale"
     *\param[in] k1 : MD5Key servant à la comparaison
     *\param[in] k2 : MD5Key servant à la comparaison
     *\return true si l'objet k1 est égale à l'objet k2 false sinon
     */
    friend bool operator== (const MD5Key&k1, const MD5Key&k2);

    /**
     * @brief operator !=
     * @param k1
     * @param k2
     * @return
     *\brief Surchagre de l'opérateur "inégale"
     *\param[in] k1 : MD5Key servant à la comparaison
     *\param[in] k2 : MD5Key servant à la comparaison
     *\return true si l'objet k1 n'est pas égale à l'objet k2 false sinon
     */
    friend bool operator!= (const MD5Key&k1, const MD5Key&k2);
};

bool operator< (const MD5Key&k1, const MD5Key&k2);
bool operator== (const MD5Key&k1, const MD5Key&k2);
bool operator!= (const MD5Key&k1, const MD5Key&k2);
std::ostream& operator<< (std::ostream& os, const MD5Key);

#endif // MD5KEY_H
