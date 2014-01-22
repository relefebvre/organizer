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
#include <QtSql>
#include <QMessageBox>
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

    ui->progressBarDouble->setValue(0);

    QVBoxLayout *layout = new QVBoxLayout;

    QDirModel *modele = new QDirModel;

    ui->vue->setModel(modele);

    layout->addWidget(ui->vue);
    ui->vue->header()->resizeSection(0,200);

    ui->start_stop->setEnabled(false);
    ui->label->setText("Selectionner un dossier à scanner");

    ui->search_double->setEnabled(false);
    ui->search_empty->setEnabled(false);

    ui->deleteEmpty->setEnabled(false);
    ui->deleteFile->setEnabled(false);

    connect(ui->actionAuteurs,SIGNAL(triggered()),this,SLOT(apropos()));
}

OrgView::~OrgView()
{
    delete ui;
}

void OrgView::start(std::string argv)
{
    insert(path(argv));


    try {for ( recursive_directory_iterator end, dir(argv);
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
    }}
    catch (const boost::filesystem::filesystem_error& err)
    {
        std::string s = "<font color='red'>"+std::string(err.what()) + "</font>";
        ui->status_error->setText(QString(s.c_str()));
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

void OrgView::afficherDoublons()
{
    modDbl = new DoublonModel(" ") ;

    setStatus("Recherche de doublons dans le dossier " + getRacine());
    //std::cout << "Résultats de la recherche de doublons : "<<std::endl ;

    int i = 1 ;
    unsigned long nbFilesCount = 0;
    int total = doublons.size() ;
    if (total == 0)
        total = 1 ;


    for(auto it=doublons.begin() ; it!=doublons.end() ; ++it)
    {
        if ((it->second.size()) > 1)
        {
            QString sPath;
            QString qs("Nb doublons ");
            qs += QString::number(it->second.size());


            //On ajoute une famille de path ayant la même taille au doublonTree
            modDbl->setupModelData((qs),1, modDbl->rootItem);
            //std::cout << "Nombre de doublons : "<< it->second.size() << std::endl ;

            QApplication::processEvents();

            for (auto itp=it->second.begin() ; itp!=it->second.end() ; ++itp)
            {
                sPath = itp->c_str() ;

                modDbl->setupModelData((sPath),1, modDbl->rootItem->child(i));
                //std::cout << itp->c_str() << std::endl ;

                sPath.clear();
                QApplication::processEvents();
            }

            ++i ;
        }
        ++nbFilesCount;
        ui->progressBarDouble->setValue(100*nbFilesCount/total);
    }

    ui->treeView->setModel(modDbl);
    ui->progressBarDouble->setValue(100*nbFilesCount/total);
    ui->deleteFile->setEnabled(true);

    ui->treeView->expandAll();

    setStatus("Recherche de doublons terminée");
}

void OrgView::afficherEmpty()
{
    modEmpty = new DoublonModel(" ") ;
    int i = 1 ;
    QString sPath;
    int total = emptyDir.size() ;
    if (total == 0)
        total = 1 ;

    unsigned long nbFilesCount = 0;


    setStatus("Recherche de dossiers vides dans le dossier " + getRacine());
    //std::cout << "Résultats de la recherche de dossiers vides : " <<std::endl ;

    for (auto it=emptyDir.begin() ; it!=emptyDir.end() ; ++it)
    {
        sPath = it->c_str() ;

        modEmpty->setupModelData((sPath),2, modEmpty->rootItem);
        //std::cout << it->c_str() << std::endl ;

        sPath.clear();

        ++i ;
        ++nbFilesCount;
        ui->progressBarEmpty->setValue(100*nbFilesCount/total);
        QApplication::processEvents();

        /*ui->view_empty->append(QString(it->c_str()));
        QApplication::processEvents();*/
    }

    ui->treeViewEmpty->setModel(modEmpty);
    ui->progressBarEmpty->setValue(100*nbFilesCount/total);

    setStatus("Recherche de dossiers vides terminée");
    ui->deleteEmpty->setEnabled(true);
}

void OrgView::setStatus(const std::string & s) const
{
    ui->status->setText(QString(s.c_str()));
}

void OrgView::deleteFile()
{
    QString path  ;
    std::string cmd ;
    QSqlQuery query;


    QItemSelectionModel *selection = ui->treeView->selectionModel();
    QModelIndexList listeSelection ;
    listeSelection = selection->selectedIndexes() ;
    ui->treeView->clearSelection();

    for(int i = 0 ; i< listeSelection.size() ; ++i)
    {
        path = modDbl->dataPath(listeSelection[i], Qt::DisplayRole).toString() ;
        cmd = "rm -f \""+path.toStdString()+"\"" ;   //Création de la commande de suppression
        system(cmd.c_str());    //Execution de la commande
        std::cout << "Fichier "+path.toStdString()+" supprimé." << std::endl ;


        query.prepare("DELETE FROM fic WHERE path=:path");
        query.bindValue(":path",path);
        query.exec();
    }

    searchDouble();
    afficherDoublons();

}

void OrgView::deleteRepertory()
{
    QString path  ;
    std::string cmd ;
    QSqlQuery query;


    QItemSelectionModel *selection = ui->treeViewEmpty->selectionModel();
    QModelIndexList listeSelection ;
    listeSelection = selection->selectedIndexes() ;
    ui->treeViewEmpty->clearSelection();

    for(int i = 0 ; i< listeSelection.size() ; ++i)
    {
        path = modEmpty->dataPath(listeSelection[i], Qt::DisplayRole).toString() ;
        cmd = "rm -rf \""+path.toStdString()+"\"" ;   //Création de la commande de suppression
        system(cmd.c_str());    //Execution de la commande
        std::cout << "Dossier "+path.toStdString()+" supprimé." << std::endl ;

        query.prepare("DELETE FROM dir WHERE path=:path");
        query.bindValue(":path",path);
        query.exec();
    }

    searchEmpty();
    afficherEmpty();
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
        tmp << "\t\tDossier a scanner !";

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

void OrgView::on_deleteFile_clicked()
{
    deleteFile() ;
}

void OrgView::apropos()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Auteurs");
    msgBox.setText("Application réalisée par : \nDucros Alix & Lefebvre Rémi");
    msgBox.exec();
}

void OrgView::on_deleteEmpty_clicked()
{

    deleteRepertory();
}
