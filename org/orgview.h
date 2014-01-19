#ifndef ORGVIEW_H
#define ORGVIEW_H

/**
 *\file orgview.h
 *\author Ducros & Lefebvre
 *\date 21 Janvier 2014
 *\brief Définit l'afichage de l'application
 */

#include <QMainWindow>
#include <QModelIndex>
#include <QGroupBox>
#include <QItemSelectionModel>
#include "doublonmodel.h"
#include "organizer.h"

namespace Ui {
class OrgView;
}

/**
 *@brief Classe représentant l'affichage de l'application
 *\class OrgView
 */

class OrgView : public QMainWindow, public Organizer
{
    Q_OBJECT
    bool runing;    /**< Indique l'état de l'application*/

public:
    explicit OrgView(QWidget *parent = 0);
    ~OrgView();
    void start(std::string argv);
    void affiche(const QString & s) const;
    void afficherDoublons();
    void afficherEmpty();
    void setStatus(const std::string &s) const;
    void deleteFile() ;



private slots:
    void on_start_stop_clicked();
    void setChemin( const QModelIndex & index );
    void on_search_double_clicked();
    void on_search_empty_clicked();
    void on_deleteFile_clicked();
    void apropos();

private:
    Ui::OrgView *ui;
    QItemSelectionModel *selectionModel;
    DoublonModel * modDbl ;
    DoublonModel * modEmpty ;


signals:

};

#endif // ORGVIEW_H
