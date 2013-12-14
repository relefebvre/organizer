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


using namespace boost::filesystem;
using namespace std;

int main(int argc, char* argv[])
{
   std::list<path> doublons;

   Organizer org;

    for ( recursive_directory_iterator end, dir(argv[1]);
          dir != end; ++dir ) {
        path ph = *dir;

        if (ph.filename().c_str()[0] == '.')
        {
            dir.no_push();
            continue;
        }

        org.insert(*dir);
    }

    org.searchDouble();

    org.afficherDoublons();

    return 0;
}

