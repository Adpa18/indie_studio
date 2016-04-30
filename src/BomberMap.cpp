//
// BomberMap.cpp for MAP in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 18:14:09 2016 Victor Gouet
// Last update Sat Apr 30 10:07:54 2016 Victor Gouet
//

#include <cstdlib>
#include "../include/BomberMap.hpp"
#include <Player.hpp>

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

void BomberMap::serialize(const std::string &saveFile) const
{
    irr::IrrlichtDevice  *device = IrrlichtController::getDevice();
    irr::io::IAttributes *attributes;
    irr::io::IXMLWriter *writter;

    writter = device->getFileSystem()->createXMLWriter(saveFile.c_str());
    writter->writeXMLHeader();
    writter->writeElement(L"Map");
    writter->writeLineBreak();
    for (std::vector<AGameObject *>::const_iterator it = _objects.begin(), end = _objects.end(); it != end; ++it)
    {
        attributes = device->getFileSystem()->createEmptyAttributes();
        (**it)->serializeAttributes(attributes);
        attributes->write(writter, false, L"attributes");
        delete(attributes);
    }
    writter->writeClosingTag(L"Map");
    writter->drop();
}

void BomberMap::deserialize(const std::string &loadFile)
{
    irr::IrrlichtDevice *device = IrrlichtController::getDevice();
    irr::io::IAttributes *attributes;
    irr::io::IXMLReader *reader;
    EventGame   eventGame;
    AGameObject *toPush;
    irr::core::stringw mapelem(L"attributes");

    reader = device->getFileSystem()->createXMLReader(loadFile.c_str());
    while (reader->read())
    {
        if (reader->getNodeType() == irr::io::EXN_ELEMENT && mapelem.equals_ignore_case(reader->getNodeName()))
        {
            Player  *character;

            attributes = device->getFileSystem()->createEmptyAttributes();
            attributes->read(reader, true);
            toPush = new Player("Richard", irr::core::vector3df(0, 0, 0), "../media/pikachu.md2", "../media/pikachu.png", 42, eventGame);
            (*toPush)->deserializeAttributes(attributes);
            character = dynamic_cast<Player *>(toPush);
            if (character != NULL)
                character->setName((*toPush)->getName());
            _objects.push_back(toPush);
            attributes->drop();
        }
    }
    reader->drop();
}
