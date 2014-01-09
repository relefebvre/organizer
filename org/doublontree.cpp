#include "doublontree.h"


DoublonTree::DoublonTree(const QList<QVariant> &data, DoublonTree *parent)
{
    parentItem = parent ;
    itemData = data ;
}

DoublonTree::~DoublonTree()
{
    qDeleteAll(childItems) ;
}

void DoublonTree::appendChild(DoublonTree *child)
{
    childItems.append(child) ;
}

DoublonTree *DoublonTree::child(int row)
{
    return childItems.value(row) ;
}

int DoublonTree::childCount() const
{
    return childItems.count() ;
}

int DoublonTree::row() const
{
    if(parentItem)
        return parentItem->childItems.indexOf(const_cast<DoublonTree*>(this)) ;
    return 0 ;
}

int DoublonTree::columnCount() const
{
    return itemData.count() ;
}

QVariant DoublonTree::data(int column) const
{
    return itemData.value(column) ;
}

DoublonTree *DoublonTree::parent()
{
    return parentItem ;
}

