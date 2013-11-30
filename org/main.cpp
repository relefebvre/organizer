#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <map>
#include <stdint.h>


using namespace boost::filesystem;

int main(int argc, char* argv[])
{
  std::map<uint64_t,std::string> data;

  std::cout<<argv[1]<<":"<<file_size(argv[1])<<std::endl;

  for ( recursive_directory_iterator end, dir("/home");
         dir != end; ++dir ) {
      if (is_regular_file(*dir))
      {
          path ph = *dir;
          uint64_t size = file_size(*dir);
          std::string path = ph.string();
          data.insert(std::pair<uint64_t,std::string>(size,path));
          //std::cout << ph.filename() <<":"<< ph.leaf() << std::endl;
      }
  }

  std::cout<<"Résultat du find : "<<data.find(file_size(argv[1]))->second<<std::endl;

  /*std::cout<<"-----------------Affichage---------------"<<std::endl;

  for (std::map<uint64_t,std::string>::iterator it = data.begin() ; it != data.end() ; ++it)
      std::cout<<it->second<<":"<<it->first<<std::endl;*/

  return 0;
}

