//
// BomberMap.cpp for MAP in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Apr 27 18:14:09 2016 Victor Gouet
// Last update Wed Apr 27 20:09:37 2016 Victor Gouet
//

#include "../include/BomberMap.hpp"
#include <cstdlib>

BomberMap::BomberMap(std::string const &)
{
  
}

BomberMap::BomberMap(int width, int height)
{
  int		posX = -width / 2;
  int		posY = -height / 2;
  int		y;
  int		x;

  srand(time(NULL));
  y = 0;
  while (y < height)
    {
      x = 0;
      while (x < width)
	{
	  if (x % 2 == 1 && y % 2 == 1)
	    {
	  _objects.push_back(new Wall(irr::core::vector3df(x + posX, 0, y + posY) * scale));
	      // IrrlichtController::getSceneManager()->addCubeSceneNode(scale, NULL,
	      // 							      0,
	      // 							      irr::core::vector3df(x + posX, 0, y + posY) * scale);
	    }
	  else
	    {
	      _objects.push_back(new Wall(irr::core::vector3df(x + posX, 0, y + posY) * scale, Wall::Invicible));
	    }
	  ++x;
	}
      ++y;
    }
}
