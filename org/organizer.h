#ifndef ORGANIZER_H
#define ORGANIZER_H

/**
 *\file organizer.h
 *\author Ducros & Lefebvre
 *\date 21 Janvier 2014
 *\brief Définit les méthodes de l'application
 */

#include <string>
#include <stdint.h>
#include <boost/filesystem.hpp>
#include <QString>
#include <set>
#include <list>
#include <map>
#include "doublon.h"
#include "md5key.h"

/**
 * @brief Classe représentant l'application
 *\class Organizer
 */

class Organizer
{

protected:
    std::multiset<Doublon*> doublonSize;  /**< Multiset contenant les pointeurs sur les doublons de tailles identiques*/
    std::map<MD5Key,std::list<boost::filesystem::path> > doublons;  /**< Map contenant les chemins d'accès aux fichiers pour une clé MD5 donnée*/
    std::list<boost::filesystem::path> emptyDir;    /**< List contenant les chemins d'accès aux dossiers vides*/
    std::string racine; /**< Chemin d'accès de la racine de l'arborescence à scanner*/

public:

    /**
     * @brief Constructeur de la classe Organizer
     */
    Organizer();

    /**
     *@brief Créer la base de donnée sqlite3
     *@return true si la base de donnée est ouverte false sinon
     */
    bool createDB() const;

    /**
     * @brief createTable
     * @param query
     *\brief Créer une table dans la base de donnée
     *\param[in] query : Commande à exécuter pour la création de la table
     */
    void createTable(const std::string & query) const;

    /**
     * @brief insert
     *\brief Insert un chemin dans la base de donnée
     * @param p
     *\param[in] p : Chemin à insérer dans la base de donnée
     */
    void insert(const boost::filesystem::path & p) const;

    /**
     * @brief supprimerGuillemets
     *\brief Supprime les guillemets d'une chaine de caractères
     * @param Qstr
     *\param[in] Qstr : QString contenant la chaine avec guillemets
     * @return
     *\return Chaîne de caractères sans guillemets
     */
    const std::string supprimerGuillemets(const QString & Qstr);

    /**
     * @brief md5
     *\brief Calcul la somme MD5 d'un fichier
     * @param Qstr
     *\param[in,out] d : Pointeur sur un Doublon
     */
    void md5(Doublon* d);

    /**
     * @brief searchDouble
     *\brief Recherche les fichiers en double
     */
    void searchDouble(void);

    /**
     * @brief searchBySize
     * @param size
     *\brief Recherche les fichiers ayant la même taille
     *\param[in] size : Taille de fichier
     */
    void searchBySize(const uint64_t size);

    /**
     * @brief setRacine
     *\brief Initialise la racine de l'arborecence
     *\param[in] racine : Chemin d'un repertoire
     */
    void setRacine(const std::string & racine);

    /**
     * @brief getRacine
     * @return
     *\brief Récupérérer la racine de l'arborecence
     *\return Le chemin de la racine de l'arborecence
     */
    const std::string & getRacine() const;

    /**
     * @brief searchEmpty
     *\brief Recherche de dossiers vide
     */
    void searchEmpty();

    /**
     * @brief isUpdate
     * @param p
     * @return
     *\brief Test si un dossier est à jour dans la base de données
     *\param[in] p : Chemin d'accès à un repertoire
     *\return true si le repertoire est à jour
     */
    bool isUpdate(const boost::filesystem::path & p) const;
};

#endif // ORGANIZER_H
