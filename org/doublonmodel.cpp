#include "doublonmodel.h"
#include <iostream>

DoublonModel::DoublonModel(const QString &data, QObject *parent) :
    QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    rootData << "Taille";
    rootItem = new DoublonTree(rootData,0);
    setupModelData((data),0, rootItem);
}

DoublonModel::~DoublonModel()
{
    delete rootItem ;
}

QModelIndex DoublonModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
         return QModelIndex();

     DoublonTree *parentItem;

     if (!parent.isValid())
         parentItem = rootItem;
     else
         parentItem = static_cast<DoublonTree*>(parent.internalPointer());

     DoublonTree *childItem = parentItem->child(row);
     if (childItem)
         return createIndex(row, column, childItem);
     else
         return QModelIndex();
}

QModelIndex DoublonModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    DoublonTree *childItem = static_cast<DoublonTree*>(index.internalPointer());
    DoublonTree *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int DoublonModel::rowCount(const QModelIndex &parent) const
{
    DoublonTree *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<DoublonTree*>(parent.internalPointer());

    return parentItem->childCount();

}

int DoublonModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<DoublonTree*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

void DoublonModel::setupModelData(const QString &line,const u_int8_t type, DoublonTree *parent)
{
    QVariant li ;


    li= line ;

    parent->appendChild(new DoublonTree(li,type, parent));

}

QVariant DoublonModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    DoublonTree *item = static_cast<DoublonTree*>(index.internalPointer());

    if (role != Qt::DisplayRole)
        return QVariant();

    return item->data();
}

QVariant DoublonModel::dataPath(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    DoublonTree *item = static_cast<DoublonTree*>(index.internalPointer());

    if (role != Qt::DisplayRole)
        return QVariant();


    if(item -> getType() != 1)
        return QVariant() ;


    return item->data();
}



Qt::ItemFlags DoublonModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    if ( index.column() == 1 )
            flags |= Qt::ItemIsUserCheckable;

    return flags ;
}

QVariant DoublonModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data();

    return QVariant();
}
