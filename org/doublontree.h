#ifndef DOUBLONTREE_H
#define DOUBLONTREE_H

#include "doublon.h"
#include <QList>
#include <QVariant>


class DoublonTree
{
public:
     DoublonTree(const QVariant &data, const u_int8_t type, DoublonTree *parent = 0);
     ~DoublonTree();

     void appendChild(DoublonTree *child);

     DoublonTree *child(int row);
     int childCount() const;
     QVariant data() const;
     int columnCount() const ;
     int row() const;
     DoublonTree *parent();

     u_int8_t getType() ;

 private:
     QList<DoublonTree*> childItems;
     DoublonTree *parentItem;
     QVariant itemData;


     u_int8_t type ; // 0 -> dossier de l'arbre ; 1 -> fichier ; 2 -> dossier


};

#endif // DOUBLONTREE_H
