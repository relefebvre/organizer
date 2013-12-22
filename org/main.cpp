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
<<<<<<< HEAD
#include "organizer.h"
=======
//#include "organizer.h"
>>>>>>> 1b83879d73c310b0975b0bd8a93da4031f3a8b31
#include "orgview.h"
#include <QApplication>

using namespace boost::filesystem;
using namespace std;

int main(int argc, char* argv[])
{

    QApplication app(argc, argv);
    OrgView org;
<<<<<<< HEAD
    org.setRacine(argv[1]);
    org.show();
    return app.exec();
=======
    org.show();
    return app.exec();
;
>>>>>>> 1b83879d73c310b0975b0bd8a93da4031f3a8b31
}

