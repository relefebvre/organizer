#ifndef ORGVIEW_H
#define ORGVIEW_H

#include <QMainWindow>
#include "organizer.h"

namespace Ui {
class OrgView;
}

class OrgView : public QMainWindow, public Organizer
{
    Q_OBJECT
    bool runing;

public:
    explicit OrgView(QWidget *parent = 0);
    ~OrgView();
    void start(std::string argv);
    void affiche(QString s);


private slots:
    void on_start_stop_clicked();

private:
    Ui::OrgView *ui;
};

#endif // ORGVIEW_H
