#ifndef DOUBLONMODEL_H
#define DOUBLONMODEL_H

/**
 *\file doublonmodel.h
 *\author Ducros & Lefebvre
 *\date 21 Janvier 2014
 *\brief Définit le modèle représentant les doublons
 */

#include <QAbstractItemModel>
#include "doublontree.h"
#include "doublon.h"
#include <QStringList>

/**
 * @brief la classe DoublonModel permettant la représentation en arbre d'une liste de doubons
 *\class DoublonModel
 */

class DoublonModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    /**
     * @brief Constructeur de la classe DoublonModel
     * @param data : données du noeud
     * @param parent : noeud parent (par défault 0 : noeud "racine")
     */
    explicit DoublonModel(const QString &data, QObject *parent = 0);
    ~DoublonModel();
    /**
      * @brief méthode permettant de récupérer les données du neoud
      * @param index : index du noeud duquel récuprer les données
      * @param role
      * @return données du noeud ciblé
      */
     QVariant data(const QModelIndex &index, int role) const;

     /**
      * @brief méthode permettant de récupérer les données du noeud en tenant compte du type du noeud (noeud informatif, noeud représentant un fichier, ou un dossier)
      * @param index : index du noeud duquel récupérer les données
      * @param role
      * @return données du noeud ciblé
      */
     QVariant dataPath(const QModelIndex &index, int role) const;
     /**
      * @brief méthode s'assurant que la vue utilise ce modèle en lecture seule
      * @param index
      * @return
      */
     Qt::ItemFlags flags(const QModelIndex &index) const;
     /**
      * @brief méthode permettant de renseigner le header de la vue dans laquelle est affiché le modèle
      * @param section
      * @param orientation
      * @param role
      * @return
      */
     QVariant headerData(int section, Qt::Orientation orientation,
                         int role = Qt::DisplayRole) const;
     /**
      * @brief méthode permettant de retrouver l'index d'un élément à patir de sa ligne et sa colonne
      * @param row
      * @param column
      * @param parent
      * @return Index de l'élément ciblé
      */
     QModelIndex index(int row, int column,
                       const QModelIndex &parent = QModelIndex()) const;
     /**
      * @brief méthode renvoyant l'index pointant vers le parent du noeud ciblé
      * @param index : index du noeud dont on cherche le Papa
      * @return Index sur le père
      */
     QModelIndex parent(const QModelIndex &index) const;

     /**
     * @brief méthode renvoyant ne nombre de lignes
     * @param parent
     * @return Nombre de ligne
     */
     int rowCount(const QModelIndex &parent = QModelIndex()) const;
     /**
      * @brief méthode renvoyant le nombre de colonnes
      * @param parent
      * @return Nombre de colonnes
      */
     int columnCount(const QModelIndex &parent = QModelIndex()) const;

     /**
      * @brief méthode permettant de créer de nouveaux noeuds
      * @param line : donées du noeud
      * @param type : type du noeud (informatif=0, fichier=1 ou dossier=2)
      * @param parent : parent du noeud à créer
      */
     void setupModelData(const QString &line, const u_int8_t type, DoublonTree *parent);
     /**
      * @brief Noeud racine du modèle
      */
     DoublonTree *rootItem;


};

#endif // DOUBLONMODEL_H
