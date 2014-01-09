#ifndef DOUBLONTREE_H
#define DOUBLONTREE_H

#include "doublon.h"
#include <QList>
#include <QVariant>


class DoublonTree
{
public:
     DoublonTree(const QList<QVariant> &data, DoublonTree *parent = 0);
     ~DoublonTree();

     void appendChild(DoublonTree *child);

     DoublonTree *child(int row);
     int childCount() const;
     int columnCount() const;
     QVariant data(int column) const;
     int row() const;
     DoublonTree *parent();

     bool isChecked() const ;
     void setChecked(bool set) ;

 private:
     QList<DoublonTree*> childItems;
     QList<QVariant> itemData;
     DoublonTree *parentItem;
     bool checked ;


};

#endif // DOUBLONTREE_H
