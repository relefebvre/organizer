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
#include "doublonmodel.h"



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
    ui->vue->header()->resizeSection(0,200);

    ui->start_stop->setEnabled(false);
    ui->label->setText("Selectionner un dossier à scanner");

    ui->search_double->setEnabled(false);
    ui->search_empty->setEnabled(false);

    layout->addWidget(ui->treeView);



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

     ui->start_stop->setText("Scanner");

     ui->search_double->setEnabled(true);
     ui->search_empty->setEnabled(true);

     if (!runing)
        setStatus("ATTENTION le dossier " + getRacine() + " n'a pas été scanné complètement");
     else
        setStatus("Dossier " + getRacine() + " scanné");

     runing = false;
}

void OrgView::affiche(const QString &s) const
{
    ui->textBrowser->append(s);
    QApplication::processEvents();
}

void OrgView::afficherDoublons() const
{
    setStatus("Recherche de doublons dans le dossier " + getRacine());

    DoublonModel * mod = new DoublonModel(" ") ;
    int i = 1 ;



    for( std::map<uint64_t,std::list<boost::filesystem::path> >::const_iterator it=doublons.begin() ; it!=doublons.end() ; ++it)
    {
        QString sPath;
        QString qs("Taille ");
        qs += QString::number(it->first);
        QList<QVariant> taille ;
        taille << qs ;



        //On ajoute une famille de path ayant la même taille au doublonTree
        mod->setupModelData(qs.split(QString("\n")), mod->rootItem);

        QApplication::processEvents();

        for (std::list<boost::filesystem::path>::const_iterator itp=it->second.begin() ; itp!=it->second.end() ; ++itp)
        {
            sPath += qs ;
            sPath += "\n" ;
            sPath += itp->c_str() ;

            mod->setupModelData(sPath.split(QString("\n")), mod->rootItem->child(i));

            sPath.clear();
            QApplication::processEvents();
        }

        ++i ;
    }

    ui->treeView->setModel(mod);

    setStatus("Recherche de doublons terminée");
}

void OrgView::afficherEmpty() const
{
    setStatus("Recherche de dossiers vides dans le dossier " + getRacine());

    for (std::list<boost::filesystem::path>::const_iterator it=emptyDir.begin() ; it!=emptyDir.end() ; ++it)
    {
        ui->view_empty->append(QString(it->c_str()));
        QApplication::processEvents();
    }

    setStatus("Recherche de dossiers vides terminée");
}

void OrgView::setStatus(const std::string & s) const
{
    ui->status->setText(QString(s.c_str()));
}


void OrgView::on_start_stop_clicked()
{
    if (!runing)
    {
        std::string status = "Scan du dossier " + getRacine() + "...";
        setStatus("Scan du dossier " + getRacine() + "...");
        runing = true;
        ui->start_stop->setText("Stop");
        start(getRacine());
    }
    else
    {
        runing = false;
        ui->start_stop->setText("Scanné");

    }
}

void OrgView::setChemin(const QModelIndex &index)
{
    QDirModel dir;
    ui->search_double->setEnabled(false);
    ui->search_empty->setEnabled(false);
    setRacine(dir.fileInfo(index).absoluteFilePath().toStdString());
    std::stringstream tmp;
    tmp << getRacine();
    if (isUpdate(getRacine()))
    {
        tmp << "\t\tDossier à jour !";
        ui->search_double->setEnabled(true);
        ui->search_empty->setEnabled(true);
    }
    else
        tmp << "\t\tDossier scanné !";

    ui->label->setText(QString(std::string(tmp.str()).c_str()));
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
