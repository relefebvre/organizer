#ifndef ORGVIEW_H
#define ORGVIEW_H

#include <QMainWindow>
<<<<<<< HEAD
#include "organizer.h"
=======
>>>>>>> 1b83879d73c310b0975b0bd8a93da4031f3a8b31

namespace Ui {
class OrgView;
}

<<<<<<< HEAD
class OrgView : public QMainWindow, public Organizer
{
    Q_OBJECT
    bool runing;
=======
class OrgView : public QMainWindow
{
    Q_OBJECT
>>>>>>> 1b83879d73c310b0975b0bd8a93da4031f3a8b31

public:
    explicit OrgView(QWidget *parent = 0);
    ~OrgView();
<<<<<<< HEAD
    void start(std::string argv);
    void affiche(QString s);


private slots:
    void on_start_stop_clicked();
=======
    int main(std::string argv);
    void affiche(QString s);



private slots:
    void on_go_clicked();
>>>>>>> 1b83879d73c310b0975b0bd8a93da4031f3a8b31

private:
    Ui::OrgView *ui;
};

#endif // ORGVIEW_H
