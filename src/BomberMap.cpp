//
// BomberMap.cpp for MAP in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Apr 27 18:14:09 2016 Victor Gouet
// Last update Thu Apr 28 09:59:25 2016 Victor Gouet
//

#include "../include/BomberMap.hpp"
#include <cstdlib>

BomberMap::BomberMap(std::string const &)
{
  
}

BomberMap::BomberMap(int , int )
{
  int		posX = -11 / 2;
  int		posY = -11 / 2;
  int		y;
  int		x;

  srand(time(NULL));
  y = 0;
  while (y < 11)
    {
      x = 0;
      while (x < 11)
	{
	  if (_patron[y][x] == 'X')
	    {
	       // _objects.push_back(new Wall(irr::core::vector3df(x + posX, 0, y + posY) * scale, Wall::Invicible));

	      irr::scene::ISceneNode *node = IrrlichtController::getSceneManager()->addCubeSceneNode(scale - 2.5, 0, 1, irr::core::vector3df(x + posX, 0, y + posY) * (scale + 2.5));

	      node->setMaterialTexture(0, IrrlichtController::getDriver()->getTexture("media/caisse-metal.png"));
	    }
	  else if (_patron[y][x] == 'C')
	    {
	      // Wall	*wall = new Wall(irr::core::vector3df(x + posX, 0, y + posY) * scale
	      // 				 );

	      irr::scene::ISceneNode *node = IrrlichtController::getSceneManager()->addCubeSceneNode(scale - 2.5, 0, 1, irr::core::vector3df(x + posX, 0, y + posY) * (scale + 2.5));

	      node->setMaterialTexture(0, IrrlichtController::getDriver()->getTexture("media/caisse.png"));
	      

	      //(*wall)->setScale(irr::core::vector3df(1, 1, 1));
	      // _objects.push_back(wall);
	    }
	  ++x;
	}
      ++y;
    }
}
