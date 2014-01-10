#ifndef ORGVIEW_H
#define ORGVIEW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QGroupBox>
#include <QItemSelectionModel>
#include "doublonmodel.h"
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
    void affiche(const QString & s) const;
    void afficherDoublons() const;
    void afficherEmpty() const;
    void setStatus(const std::string &s) const;


private slots:
    void on_start_stop_clicked();
    void setChemin( const QModelIndex & index );

    void on_search_double_clicked();

    void on_search_empty_clicked();
private:
    Ui::OrgView *ui;
    QItemSelectionModel *selectionModel;
    DoublonModel * mod ;


signals:

};

#endif // ORGVIEW_H
