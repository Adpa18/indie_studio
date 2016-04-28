//
// BomberMap.cpp for MAP in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 18:14:09 2016 Victor Gouet
// Last update Thu Apr 28 11:51:15 2016 Victor Gouet
//

#include "../include/BomberMap.hpp"
#include <cstdlib>

BomberMap::BomberMap(std::string const &)
{

}



BomberMap::BomberMap()
{
  generateMap();
  generateGround();
}

void			BomberMap::generateGround()
{
  // IrrlichtController::getSceneManager()->addTerrainSceneNode("/home/gouet_v/Downloads/irrlicht-1.8.3/media/wall.bmp");// addT
}

void			BomberMap::generateMap()
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
            new Wall(irr::core::vector3df(x + posX, 0, y + posY) * (IrrlichtController::scale), Wall::Invicible);
	    //   irr::scene::ISceneNode *node = IrrlichtController::getSceneManager()->addCubeSceneNode(IrrlichtController::scale, 0, 1, irr::core::vector3df(x + posX, 0, y + posY) * (IrrlichtController::scale));
          //
	    //   node->setMaterialTexture(0, IrrlichtController::getDriver()->getTexture("media/caisse-metal.png"));
	    }
	  else if (_patron[y][x] == 'C')
	    {
            new Wall(irr::core::vector3df(x + posX, 0, y + posY) * (IrrlichtController::scale));
	    //   irr::scene::ISceneNode *node = IrrlichtController::getSceneManager()->addCubeSceneNode(IrrlichtController::scale, 0, 1, irr::core::vector3df(x + posX, 0, y + posY) * (IrrlichtController::scale));
          //
	    //   node->setMaterialTexture(0, IrrlichtController::getDriver()->getTexture("media/caisse.png"));

	    }
	  ++x;
	}
      ++y;
    }

}
