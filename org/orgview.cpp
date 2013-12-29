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
#include <QFileSystemModel>

using namespace boost::filesystem;


OrgView::OrgView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OrgView)
{
    ui->setupUi(this);
    runing = false;
    connect(ui->vue,SIGNAL(clicked(QModelIndex const&)),this,SLOT(setChemin(QModelIndex const&)));

    QVBoxLayout *layout = new QVBoxLayout;

    QDirModel *modele = new QDirModel;

    ui->vue->setModel(modele);

    layout->addWidget(ui->vue);

    ui->start_stop->setEnabled(false);
    ui->label->setText("Selectionner un dossier à scanner");
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

         if (!runing)
             break;
     }
     runing = false;
     ui->start_stop->setText("Go");


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
        runing = false;
        ui->start_stop->setText("Go");
    }
}

void OrgView::setChemin(const QModelIndex &index)
{
    QDirModel dir;
    setRacine(dir.fileInfo(index).absoluteFilePath().toStdString());
    ui->label->setText(QString(getRacine().c_str()));
    ui->start_stop->setEnabled(true);
}
