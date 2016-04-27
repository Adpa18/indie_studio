//
// BomberMap.cpp for MAP in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Apr 27 18:14:09 2016 Victor Gouet
// Last update Wed Apr 27 19:18:34 2016 Victor Gouet
//

#include "../include/BomberMap.hpp"

BomberMap::BomberMap(std::string const &)
{
  
}

BomberMap::BomberMap(int width, int height)
{
  int		posX = -width / 2;
  int		posY = -height / 2;
  int		y;
  int		x;

  y = 0;
  while (y < height)
    {
      x = 0;
      while (x < width)
	{
	  IrrlichtController::getSceneManager()->addCubeSceneNode(20, NULL,
								  0, irr::core::vector3df(x + posX, 0, y + posY) * scale);
	  // _objects.push_back(
			     // new Wall(irr::core::vector3df(x, 0, y) * scale,
			     // 	      Wall::Destructible)
			     // );
	  ++x;
	}
      ++y;
    }
}
