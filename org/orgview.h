#ifndef ORGVIEW_H
#define ORGVIEW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QGroupBox>
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
    void afficherEmpty();
    void setStatus(std::string s);


private slots:
    void on_start_stop_clicked();
    void setChemin( const QModelIndex & index );

    void on_search_double_clicked();

    void on_search_empty_clicked();

private:
    Ui::OrgView *ui;

signals:

    //void clicked ( const QModelIndex & index );

};

#endif // ORGVIEW_H
