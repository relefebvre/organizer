#ifndef DOUBLONMODEL_H
#define DOUBLONMODEL_H

#include <QAbstractItemModel>
#include "doublontree.h"
#include "doublon.h"
#include <QStringList>


class DoublonModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit DoublonModel(const QString &data, QObject *parent = 0);
    ~DoublonModel();

     QVariant data(const QModelIndex &index, int role) const;
     Qt::ItemFlags flags(const QModelIndex &index) const;
     QVariant headerData(int section, Qt::Orientation orientation,
                         int role = Qt::DisplayRole) const;
     QModelIndex index(int row, int column,
                       const QModelIndex &parent = QModelIndex()) const;
     QModelIndex parent(const QModelIndex &index) const;
     int rowCount(const QModelIndex &parent = QModelIndex()) const;
     int columnCount(const QModelIndex &parent = QModelIndex()) const;

     DoublonTree *rootItem;

     void setupModelData(const QStringList &lines, DoublonTree *parent);


private:

};

#endif // DOUBLONMODEL_H
