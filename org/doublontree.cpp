#include "doublontree.h"


DoublonTree::DoublonTree(const QVariant &data, const u_int8_t type, DoublonTree *parent)
{
    this->type = type ;
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
    return 1 ;
}

QVariant DoublonTree::data() const
{
    return itemData ;
}

DoublonTree *DoublonTree::parent()
{
    return parentItem ;
}


u_int8_t DoublonTree::getType()
{
    return type ;
}

