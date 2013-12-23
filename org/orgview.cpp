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
#include <QVBoxLayout>
#include <QDirModel>

using namespace boost::filesystem;


OrgView::OrgView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OrgView)
{
    ui->setupUi(this);
    runing = false;


    QVBoxLayout *layout = new QVBoxLayout;

    QDirModel *modele = new QDirModel;

    ui->vue->setModel(modele);

    layout->addWidget(ui->vue);
}

OrgView::~OrgView()
{
    delete ui;
}

void OrgView::start(std::string argv)
{
    std::list<path> doublons;

     for ( recursive_directory_iterator end, dir(argv);
           dir != end; ++dir ) {
         path ph = *dir;

         if (ph.filename().c_str()[0] == '.')
         {
             dir.no_push();
             continue;
         }

         insert(*dir);
         affiche(QString(ph.c_str()));
     }

     //org.searchDouble();

     //org.afficherDoublons();
}

void OrgView::affiche(QString s)
{
    ui->textBrowser->append(s);
    ui->textBrowser->repaint();
}



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
}
