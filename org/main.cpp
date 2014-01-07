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
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QApplication app(argc, argv);
    OrgView org;
    org.show();
    return app.exec();
}

