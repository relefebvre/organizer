#ifndef DOUBLONTREE_H
#define DOUBLONTREE_H

#include "doublon.h"
#include <QList>
#include <QVariant>

/**
 *\file doublontree.h
 *\author Ducros & Lefebvre
 *\date 21 Janvier 2014
 *\brief Définit la structure d'un noeud de l'arbre de doublons
 */

/**
 * @brief La classe DoublonTree
 *\class DoublonTree
 */
class DoublonTree
{
public:
    /**
      * @brief Constructeur de la classe DoublonTree
      * @param data : données du noeud à construire
      * @param type : type du neoud (informatif, fichier, dossier)
      * @param parent : pointeur sur le parent du noeud (par défaut construction d'un noeud "racine")
      */
     DoublonTree(const QVariant &data, const u_int8_t type, DoublonTree *parent = 0);
     /**
      * @brief Destructeur de la classe DoublonTree
      */
     ~DoublonTree();
     /**
      * @brief méthode permattant d'ajouter un fils au noeud
      * @param Pointeur sur le noeud à assimiler en tant que fils
      */
     void appendChild(DoublonTree *child);
     /**
      * @brief méthode permettant de récupérer un fils en fonction d'une ligne
      * @param row : ligne du fils qu'on veut récupérer
      * @return : Pointeur sur le fils ciblé
      */
     DoublonTree *child(int row);
     /**
      * @brief méthode qui compte le nombre de fils
      * @return Nombre de fils
      */
     int childCount() const;
     /**
      * @brief méthode permettant de récupérer les données du noeud
      * @return les données sous forme de QVariant
      */
     QVariant data() const;
     /**
      * @brief méthode permettant de récupérer le nombre de colonnes nécessaire à l'affichage des données
      * @return 1
      */
     int columnCount() const ;
     /**
      * @brief méthode permettant de récupérer le numéro de ligne à laquelle se trouve ce noeud
      * @return Numéro de ligne
      */
     int row() const;
     /**
      * @brief méthode renvoyant le parent du noeud ciblé
      * @return pointeur sur le papa
      */
     DoublonTree *parent();
     /**
      * @brief méthode permettant de récupérer la type du noeud
      * @return Type du noeud
      */
     u_int8_t getType() ;

 private:
     /**
      * @brief Liste des fils
      */
     QList<DoublonTree*> childItems;
     /**
      * @brief Noeud père
      */
     DoublonTree *parentItem;
     /**
      * @brief données du noeud
      */
     QVariant itemData;

     /**
      * @brief type du noeud 0 = informatif, 1 = fichier, 2 = dossier
      */
     u_int8_t type ;


};

#endif // DOUBLONTREE_H
