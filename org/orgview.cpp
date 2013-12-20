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
}

OrgView::~OrgView()
{
    delete ui;
}

int OrgView::main(std::string argv)
{
    std::list<path> doublons;

    Organizer org;

     for ( recursive_directory_iterator end, dir(argv);
           dir != end; ++dir ) {
         path ph = *dir;

         if (ph.filename().c_str()[0] == '.')
         {
             dir.no_push();
             continue;
         }

         org.insert(*dir);
         //std::cout<<ph.c_str()<<std::endl;
         affiche(QString(ph.c_str()));
     }

     org.searchDouble();

     org.afficherDoublons();

     return 0;
}

void OrgView::affiche(QString s)
{
    ui->textBrowser->append(s);
    ui->textBrowser->repaint();
}

void OrgView::on_go_clicked()
{
    main("/home/alix/");
}
