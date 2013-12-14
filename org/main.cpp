#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <map>
#include <stdint.h>
#include <QtSql>
#include <QSqlDatabase>
#include <sstream>
#include <tomcrypt.h>


using namespace boost::filesystem;

int main(int argc, char* argv[])
{
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName("db");
  bool ok = db.open();
  std::cout<<"Ouverture db : "<<ok<<std::endl;

  QSqlQuery query;

  std::cout<<query.exec("CREATE TABLE fic(size integer,path varchar(1000) UNIQUE);")<<std::endl;
  std::cout<<query.exec("CREATE TABLE dir(empty bool,path varchar(1000) UNIQUE);")<<std::endl;

  for ( recursive_directory_iterator end, dir(argv[1]);
         dir != end; ++dir ) {
      path ph = *dir;

      if (ph.filename().c_str()[0] == '.')
      {
          dir.no_push();
          continue;
      }

      std::string path = ph.string();

      std::cout<<path<<std::endl;

      if (is_regular_file(*dir))
      {
          uint64_t size = file_size(*dir);
          std::stringstream Ssize;
          Ssize << size;
          query.prepare("INSERT INTO fic(size, path)"
                        "VALUES (:size, :path);");
          query.bindValue(":size", Ssize.str().c_str());
          query.bindValue(":path", path.c_str());
      }
      if (is_directory(*dir))
      {
          query.prepare("INSERT INTO dir(empty, path)"
                        "VALUES (:empty, :path);");
          query.bindValue(":empty",is_empty(ph));
          query.bindValue(":path", path.c_str());
      }
      query.exec();
  }




  return 0;
}

