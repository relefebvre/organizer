#include <iostream>
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
#include "orgview.h"
#include <QApplication>

using namespace boost::filesystem;
using namespace std;

int main(int argc, char* argv[])
{

    QApplication app(argc, argv);
    OrgView org;
    org.setRacine(argv[1]);
    org.show();
    return app.exec();
}

