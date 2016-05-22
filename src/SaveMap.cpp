//
// SaveMap.cpp for SAVE in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Sun May 22 21:01:37 2016 Victor Gouet
// Last update Sun May 22 22:33:52 2016 Victor Gouet
//

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <fstream>
#include "../include/SaveMap.hpp"
#include "../include/BomberMap.hpp"
#include "../include/Wall.hpp"


SaveMap::SaveMap()
{

}

SaveMap::~SaveMap()
{

}

void		SaveMap::save()
{
  mkdir("tmp", 0777);
  if (chdir("tmp") == -1)
    {
      std::cout << "failed to load map" << std::endl;
      return ;
    }
  std::map<AGameObject *, irr::core::vector2df> const & objs = BomberMap::getMap()->getObjects();

  for (std::map<AGameObject *, irr::core::vector2df>::const_iterator it = objs.begin(), end = objs.end() ; it != end ; ++it)
    {
      Wall	*wall;
      if ((wall = dynamic_cast<Wall *>(it->first)))
	{
	  std::string	fileName = "wall" +
	    std::to_string(it->second.X) +
	    std::to_string(it->second.Y);
	  std::cout << fileName << std::endl;

	  wall->save(fileName);
	}
    }
  chdir("..");
}

void		SaveMap::load(std::string const &directory)
{
  DIR		*dir;
  struct dirent	*dirent;

  if ((dir = opendir(directory.c_str())) == NULL)
    {
      std::cerr << "failed to open dir" + directory << std::endl;
      return ;
    }
  while ((dirent = readdir(dir)))
    {
      std::ifstream	ifs;
      std::string	file = directory + "/" + std::string(dirent->d_name);

      std::cout << file << std::endl;
      ifs.open(file.c_str(), std::ios::in | std::fstream::binary);
      if (ifs.is_open())
      	{
	  Wall::DataFile	data;

	  ifs.read((char *)&data, sizeof(data));
	  data.convertToWall();
	  ifs.close();
	}
    }
}
