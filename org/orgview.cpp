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
#include <QRadioButton>
#include <QScrollArea>



using namespace boost::filesystem;


OrgView::OrgView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OrgView)
{
    ui->setupUi(this);
    runing = false;
    connect(ui->vue,SIGNAL(clicked(QModelIndex const&)),this,SLOT(setChemin(QModelIndex const&)));
    connect(ui->vue,SIGNAL(activated(QModelIndex const&)),this,SLOT(setChemin(QModelIndex const&)));
    connect(ui->vue,SIGNAL(doubleClicked(QModelIndex const&)),this,SLOT(setChemin(QModelIndex const&)));
    connect(ui->vue,SIGNAL(entered(QModelIndex const&)),this,SLOT(setChemin(QModelIndex const&)));
    connect(ui->vue,SIGNAL(pressed(QModelIndex const&)),this,SLOT(setChemin(QModelIndex const&)));

    QVBoxLayout *layout = new QVBoxLayout;

    QDirModel *modele = new QDirModel;

    ui->vue->setModel(modele);

    layout->addWidget(ui->vue);

    ui->start_stop->setEnabled(false);
    ui->label->setText("Selectionner un dossier à scanner");

    ui->search_double->setEnabled(false);
    ui->search_empty->setEnabled(false);
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

         if (boost::filesystem::is_directory(ph))
             if (isUpdate(ph))
                 continue;


         insert(*dir);
         affiche(QString(ph.c_str()));

         if (!runing)
             break;
     }
     runing = false;
     ui->start_stop->setText("Go");

     ui->search_double->setEnabled(true);
     ui->search_empty->setEnabled(true);

     setStatus("Dossier " + getRacine() + " analisé");
}

void OrgView::affiche(QString s)
{
    ui->textBrowser->append(s);
    //ui->textBrowser->repaint();
    QApplication::processEvents();

}

void OrgView::afficherDoublons()
{
    setStatus("Recherche de doublons dans le dossier " + getRacine());

    for( std::map<uint64_t,std::list<boost::filesystem::path> >::const_iterator it=doublons.begin() ; it!=doublons.end() ; ++it)
    {
        QString qs("Taille ");
        qs += QString::number(it->first);
        ui->view_double->append(qs);
        ui->view_double->repaint();
        for (std::list<boost::filesystem::path>::const_iterator itp=it->second.begin() ; itp!=it->second.end() ; ++itp)
        {
            ui->view_double->append(QString(itp->c_str()));
            QApplication::processEvents();
        }
    }

    setStatus("Recherche de doublons terminée");
}

void OrgView::afficherEmpty()
{
    setStatus("Recherche de dossiers vides dans le dossier " + getRacine());

    for (std::list<boost::filesystem::path>::const_iterator it=emptyDir.begin() ; it!=emptyDir.end() ; ++it)
    {
        ui->view_empty->append(QString(it->c_str()));
        QApplication::processEvents();
    }

    setStatus("Recherche de dossiers vides terminée");
}

void OrgView::setStatus(std::string s)
{
    ui->status->setText(QString(s.c_str()));
}


void OrgView::on_start_stop_clicked()
{
    if (!runing)
    {
        std::string status = "Analyse du dossier " + getRacine() + "...";
        setStatus("Analyse du dossier " + getRacine() + "...");
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
    ui->search_double->setEnabled(false);
    ui->search_empty->setEnabled(false);
    setRacine(dir.fileInfo(index).absoluteFilePath().toStdString());
    ui->label->setText(QString(getRacine().c_str()));
    ui->start_stop->setEnabled(true);
}

void OrgView::on_search_double_clicked()
{
    searchDouble();
    afficherDoublons();
}

void OrgView::on_search_empty_clicked()
{
    searchEmpty();
    afficherEmpty();
}
