#ifndef ORGVIEW_H
#define ORGVIEW_H

#include <QMainWindow>
#include <QModelIndex>
#include "organizer.h"

namespace Ui {
class OrgView;
}

class OrgView : public QMainWindow, public Organizer
{
    Q_OBJECT
    bool runing;
    QString chemin;

public:
    explicit OrgView(QWidget *parent = 0);
    ~OrgView();
    void start(std::string argv);
    void affiche(QString s);
    void afficherDoublons();


private slots:
    void on_start_stop_clicked();
    void setChemin( const QModelIndex & index );

    void on_search_double_clicked();

private:
    Ui::OrgView *ui;

signals:

    //void clicked ( const QModelIndex & index );

};

#endif // ORGVIEW_H
