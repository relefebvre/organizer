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

     bool isChecked() const ;
     void setChecked(bool set) ;

 private:
     QList<DoublonTree*> childItems;
     DoublonTree *parentItem;
     QVariant itemData;
     bool checked ;

     u_int8_t type ; // 0 -> dossier de l'arbre ; 1 -> fichier ; 2 -> dossier


};

#endif // DOUBLONTREE_H
