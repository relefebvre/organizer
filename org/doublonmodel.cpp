#include "doublonmodel.h"
#include <iostream>

DoublonModel::DoublonModel(const QString &data, QObject *parent) :
    QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    rootData << "Taille";
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
    /*
     *Ce bout de code fait ce qu'on attend de lui
     *
     *QList<QVariant> test ;
    QList<QVariant> test2 ;
    test2 << "Zizi" << "Bite" ;
    test << "Zob" << "Zigou";
    parent->appendChild(new DoublonTree(test, parent));
    parent->appendChild(new DoublonTree(test2, parent));
    (parent->child(0))->appendChild(new DoublonTree(test2, parent->child(0)));*/

    /*
     *Celui ci non. SegFault.
     *
     *
     *
    QList<QVariant> li ;
    QVariant str[2] ;
    std::string sstr[2] ;

    for (int i = 0; i < lines.size(); ++i)
        str[i] = lines.at(i).toLocal8Bit().constData() ;

    for(int i = 0 ; i < 2 ; ++i)
        sstr[i] = str[i].toString().toStdString() ;
    sstr[0] += sstr[1] ;
    li << str[0] ;
    */


    /*
     *Ce code ci conduit à l'absence de l'affichage du path dans le TreeView
     *
     *La QList zob quand on l'interverti avec li est elle bien affichée.
     *
     *Le problème se trouve être au niveau de la conversion du PATH ou de son assignation
     *
     */
    QList<QVariant> li ;
    QList<QVariant> zob ;
    std::string li1 ;

    zob << "Zizi" << "Zob";


    for (int i = 0; i < lines.size(); i++)
    {
        li.append(lines.at(i)) ;
    }

    foreach(QVariant qv , li)
        std::cout << qv.toString().toStdString() << std::endl ;

    std::cout << "Fin de la liste"<<std::endl ;

    parent->appendChild(new DoublonTree(li, parent));

}

QVariant DoublonModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    DoublonTree *item = static_cast<DoublonTree*>(index.internalPointer());

    if ( role == Qt::CheckStateRole && index.column() == 0 )
            return static_cast< int >( item->isChecked() ? Qt::Checked : Qt::Unchecked );


    return item->data(index.column());
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
        return rootItem->data(section);

    return QVariant();
}
