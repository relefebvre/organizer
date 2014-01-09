#include "doublonmodel.h"

DoublonModel::DoublonModel(const QString &data, QObject *parent) :
    QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    rootData << "Taille" << "Path";
    rootItem = new DoublonTree(rootData);
    setupModelData(data.split(QString("\n")), rootItem);
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

void DoublonModel::setupModelData(const QStringList &lines, DoublonTree *parent)
{
    QList<QVariant> li ;

    QStringList::const_iterator constIterator;
     for (constIterator = lines.constBegin(); constIterator != lines.constEnd(); ++constIterator)
         li << (*constIterator).toLocal8Bit().constData() ;

    parent->appendChild(new DoublonTree(li, parent));

}

QVariant DoublonModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    DoublonTree *item = static_cast<DoublonTree*>(index.internalPointer());

    return item->data(index.column());
}


Qt::ItemFlags DoublonModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant DoublonModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}
