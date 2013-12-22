#include "orgview.h"
#include "ui_orgview.h"
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <map>
#include <stdint.h>
#include <QtSql>
#include <QSqlDatabase>
#include <sstream>
#include <tomcrypt.h>
#include <list>
#include <algorithm>
#include "organizer.h"

using namespace boost::filesystem;


OrgView::OrgView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OrgView)
{
    ui->setupUi(this);
<<<<<<< HEAD
    runing = false;
=======
>>>>>>> 1b83879d73c310b0975b0bd8a93da4031f3a8b31
}

OrgView::~OrgView()
{
    delete ui;
}

<<<<<<< HEAD
void OrgView::start(std::string argv)
{
    std::list<path> doublons;

=======
int OrgView::main(std::string argv)
{
    std::list<path> doublons;

    Organizer org;

>>>>>>> 1b83879d73c310b0975b0bd8a93da4031f3a8b31
     for ( recursive_directory_iterator end, dir(argv);
           dir != end; ++dir ) {
         path ph = *dir;

         if (ph.filename().c_str()[0] == '.')
         {
             dir.no_push();
             continue;
         }

<<<<<<< HEAD
         insert(*dir);
         affiche(QString(ph.c_str()));
     }

     //org.searchDouble();

     //org.afficherDoublons();
=======
         org.insert(*dir);
         //std::cout<<ph.c_str()<<std::endl;
         affiche(QString(ph.c_str()));
     }

     org.searchDouble();

     org.afficherDoublons();

     return 0;
>>>>>>> 1b83879d73c310b0975b0bd8a93da4031f3a8b31
}

void OrgView::affiche(QString s)
{
    ui->textBrowser->append(s);
    ui->textBrowser->repaint();
}

<<<<<<< HEAD


void OrgView::on_start_stop_clicked()
{
    if (!runing)
    {
        runing = true;
        ui->start_stop->setText("Stop");
        start(getRacine());
    }
    else
    {

    }
=======
void OrgView::on_go_clicked()
{
    main("/home/alix/");
>>>>>>> 1b83879d73c310b0975b0bd8a93da4031f3a8b31
}
