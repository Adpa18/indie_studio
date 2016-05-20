//
// BomberMap.cpp for MAP in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 18:14:09 2016 Victor Gouet
// Last update Fri May 20 10:39:09 2016 Victor Gouet
//

#include <cstdlib>
#include <iostream>
#include "../include/BomberMap.hpp"
#include "../include/Texture.hpp"

BomberMap *BomberMap::bomberMap = NULL;

const int		BomberMap::size_side[3] = {11, 13, 15};

BomberMap::BomberMap(std::string const &)
{
  
}

BomberMap::BomberMap(Size mapSize) : _mapSize(mapSize)
{
  terrain_model = NULL;
  initSpawn();
}

BomberMap::~BomberMap()
{
  std::map<AGameObject*, irr::core::vector2df>::iterator it = _objects.begin();
  while (it != _objects.end())
    {
      AGameObject	*obj = (*it).first;
      delete (obj);
      it = _objects.begin();
    }
  for (std::vector<irr::scene::ILightSceneNode*>::iterator it = lightVector.begin(), end = lightVector.end() ; end != it ; ++it)
    {
      (*it)->remove();
    }
}

void            BomberMap::genMap()
{
    this->generateMap();
    this->generateGround();
}

void			BomberMap::generateGround()
{
    // irr::scene::IAnimatedMesh *terrain_model;

    terrain_model = IrrlichtController::getSceneManager()->addHillPlaneMesh("ground",
    irr::core::dimension2d<irr::f32>(25, 25), // Tile size
    irr::core::dimension2d<irr::u32>(size_side[_mapSize], size_side[_mapSize]), // Tile count
            0, // Material
            0.0f, // Hill height
    irr::core::dimension2d<irr::f32>(0.0f, 0.0f), // countHills
    irr::core::dimension2d<irr::f32>(size_side[_mapSize], size_side[_mapSize])); // textureRepeatCount

    _ground = IrrlichtController::getSceneManager()->addMeshSceneNode(terrain_model->getMesh(0));
    _ground->setMaterialTexture(0, IrrlichtController::getDriver()->getTexture(BomberManTexture::getModel("ground").texture.c_str()));
    _ground->setMaterialFlag(irr::video::EMF_LIGHTING, true);

    irr::scene::ILightSceneNode* light;
    irr::video::SLight  light_data;
//    irr::scene::ISceneNodeAnimator* anim = 0;

    light_data.Radius = 1000.0f;
    light_data.OuterCone = 50.0f;
//    light_data.Falloff = 10.f;
    light_data.Type = irr::video::ELT_SPOT;
    light_data.AmbientColor = irr::video::SColorf(0.5f, 0.5f, 0.5f);
    light_data.SpecularColor = irr::video::SColorf(0.1f,0.1f,0.1f,1);
    light_data.DiffuseColor = irr::video::SColorf(1.0f, 1.0f, 1.0f);
    light_data.CastShadows = true;

    light = IrrlichtController::getSceneManager()->addLightSceneNode();
    //light->enableCastShadow(true);
    light->setPosition(irr::core::vector3df(0, 300, 0));
    light->setLightType(irr::video::ELT_POINT);
    light->setLightData(light_data);
    lightVector.push_back(light);
//    anim = IrrlichtController::getSceneManager()->createFlyCircleAnimator(irr::core::vector3df(0, 100, 0), 250.0f);
//    light->addAnimator(anim);

     light = IrrlichtController::getSceneManager()->addLightSceneNode();
 //    light_data.DiffuseColor = irr::video::SColorf(1.0f, 0.0f, 0.0f);
     light->setLightData(light_data);
     light->setPosition(irr::core::vector3df(125, 0, -125));
     light->setRotation(irr::core::vector3df(-45, -45, 0));
     lightVector.push_back(light);

 //    anim = IrrlichtController::getSceneManager()->createFlyCircleAnimator(irr::core::vector3df(125, 0, -125), 50.0f);
 //    light->addAnimator(anim);

     light = IrrlichtController::getSceneManager()->addLightSceneNode();
 //    light_data.DiffuseColor = irr::video::SColorf(1.0f, 1.0f, 0.0f);
     light->setLightData(light_data);
     light->setPosition(irr::core::vector3df(125, 0, 125));
     light->setRotation(irr::core::vector3df(-45, 225, 0));
     lightVector.push_back(light);
 //    anim = IrrlichtController::getSceneManager()->createFlyCircleAnimator(irr::core::vector3df(125, 0, 125), 50.0f);
 //    light->addAnimator(anim);

     light = IrrlichtController::getSceneManager()->addLightSceneNode();
 //    light_data.DiffuseColor = irr::video::SColorf(0.0f, 1.0f, 0.0f);
     light->setLightData(light_data);
     light->setPosition(irr::core::vector3df(-125, 0, -125));
     light->setRotation(irr::core::vector3df(-45, 45, 0));
     lightVector.push_back(light);

 //    anim = IrrlichtController::getSceneManager()->createFlyCircleAnimator(irr::core::vector3df(-125, 0, -125), 50.0f);
 //    light->addAnimator(anim);

     light = IrrlichtController::getSceneManager()->addLightSceneNode();
 //    light_data.DiffuseColor = irr::video::SColorf(0.0f, 0.0f, 1.0f);
     light->setLightData(light_data);
     light->setPosition(irr::core::vector3df(-125, 0, 125));
     light->setRotation(irr::core::vector3df(-45, 135, 0));
     lightVector.push_back(light);

 //    anim = IrrlichtController::getSceneManager()->createFlyCircleAnimator(irr::core::vector3df(-125, 0, 125), 50.0f);
 //    light->addAnimator(anim);

//    anim->drop();


    // this->loadModel(BomberManTexture::getModel("mapCurtain")); // BadScale
    // this->loadModel(BomberManTexture::getModel("mapGoods")); // BadScale
    // this->loadModel(BomberManTexture::getModel("mapGround")); // BadScale
    // this->loadModel(BomberManTexture::getModel("mapPillar")); // OK
    // this->loadModel(BomberManTexture::getModel("mapStatue")); // BadScale
    // this->loadModel(BomberManTexture::getModel("mapTable")); // BadScale
    // this->loadModel(BomberManTexture::getModel("mapTomb")); // BadScale
    // this->loadModel(BomberManTexture::getModel("mapWall")); // BadPos Stair
}

int	BomberMap::getSize() const
{
  return (size_side[_mapSize]);
}

std::vector<irr::core::vector2df> const	&BomberMap::getSpawn() const
{
  return (_spawner);
}

void			BomberMap::initSpawn()
{
  _spawner.push_back(irr::core::vector2df(1, 1));
  _spawner.push_back(irr::core::vector2df(BomberMap::size_side[_mapSize] - 2, BomberMap::size_side[_mapSize] - 2));
  _spawner.push_back(irr::core::vector2df(BomberMap::size_side[_mapSize] - 2, 1));
  _spawner.push_back(irr::core::vector2df(1, BomberMap::size_side[_mapSize] - 2));
}

bool			BomberMap::canPutDestructibleWall(int x, int y) const
{
  int			proba;

  if ((x == 1 && y == 1) || (x == 2 && y == 1) || (x == 1 && y == 2))
    return (false);
  if ((x == BomberMap::size_side[_mapSize] - 2 && y == BomberMap::size_side[_mapSize] - 2)
      || (x == BomberMap::size_side[_mapSize] - 3 && y == BomberMap::size_side[_mapSize] - 2)
      || (x == BomberMap::size_side[_mapSize] - 2 && y == BomberMap::size_side[_mapSize] - 3))
    return (false);
  if ((x == BomberMap::size_side[_mapSize] - 2 && y == 1)
      || (x == BomberMap::size_side[_mapSize] - 3 && y == 1)
      || (x == BomberMap::size_side[_mapSize] - 2 && y == 2))
    return (false);
  if ((x == 1 && y == BomberMap::size_side[_mapSize] - 2)
      || (x == 1 && y == BomberMap::size_side[_mapSize] - 3)
      || (x == 2 && y == BomberMap::size_side[_mapSize] - 2))
    return (false);
  proba = rand() % 10;
  return (proba >= 1);
}

void			BomberMap::generateMap()
{
  srand(time(NULL));
  for (int y = 0; y < BomberMap::size_side[_mapSize]; ++y) {
    for (int x = 0; x < BomberMap::size_side[_mapSize]; ++x) {
      if (x == 0 || y == 0 || x == BomberMap::size_side[_mapSize] - 1
	  || y == BomberMap::size_side[_mapSize] - 1)
	new Wall(irr::core::vector2df(x, y), Wall::Edge);
      else if (x % 2 == 0 && y % 2 == 0 && x != 0 && y != 0)
	new Wall(irr::core::vector2df(x, y), Wall::Invicible);
      else if (canPutDestructibleWall(x, y))
	new Wall(irr::core::vector2df(x, y));
    }
  }
}

//void BomberMap::serialize(const std::string &saveFile) const
//{
//    irr::IrrlichtDevice  *device = IrrlichtController::getDevice();
//    irr::io::IAttributes *attributes;
//    irr::io::IXMLWriter *writter;
//
//    writter = device->getFileSystem()->createXMLWriter(saveFile.c_str());
//    writter->writeXMLHeader();
//    writter->writeElement(L"Map");
//    writter->writeLineBreak();
//    for (std::vector<AGameObject *>::const_iterator it = _objects.begin(), end = _objects.end(); it != end; ++it)
//    {
//        attributes = device->getFileSystem()->createEmptyAttributes();
//        (**it)->serializeAttributes(attributes);
//        attributes->write(writter, false, L"attributes");
//        delete(attributes);
//    }
//    writter->writeClosingTag(L"Map");
//    writter->drop();
//}
//
//void BomberMap::deserialize(const std::string &loadFile)
//{
//    irr::IrrlichtDevice *device = IrrlichtController::getDevice();
//    irr::io::IAttributes *attributes;
//    irr::io::IXMLReader *reader;
//    EventGame   eventGame;
//    AGameObject *toPush;
//    irr::core::stringw mapelem(L"attributes");
//
//    reader = device->getFileSystem()->createXMLReader(loadFile.c_str());
//    while (reader->read())
//    {
//        if (reader->getNodeType() == irr::io::EXN_ELEMENT && mapelem.equals_ignore_case(reader->getNodeName()))
//        {
//            Player  *character;
//
//            attributes = device->getFileSystem()->createEmptyAttributes();
//            attributes->read(reader, true);
//            toPush = new Player("Richard", irr::core::vector3df(0, 0, 0), "../media/pikachu.md2", "../media/pikachu.png", 42, eventGame);
//            (*toPush)->deserializeAttributes(attributes);
//            character = dynamic_cast<Player *>(toPush);
//            if (character != NULL)
//                character->setName((*toPush)->getName());
//            _objects.push_back(toPush);
//            attributes->drop();
//        }
//    }
//    reader->drop();
//}

void		BomberMap::newMap(Size mapSize)
{
  if (bomberMap)
    {
      delete bomberMap;
    }
  bomberMap = new BomberMap(mapSize);  
}

void		BomberMap::deleteMap()
{
   if (bomberMap)
    {
      delete bomberMap;
    }
   bomberMap = NULL;
}

bool		BomberMap::isInstantiate()
{
  if (bomberMap)
    return (true);
  return (false);
}

BomberMap       * BomberMap::getMap()
{
    if (!bomberMap) {
        bomberMap = new BomberMap();
    }
    return (bomberMap);
}

std::vector<AGameObject *> const &BomberMap::getCharacters() const
{
  return (_characters);
}

void  BomberMap::add(AGameObject* obj, const irr::core::vector2df &pos)
{
  this->_objects[obj] = pos;
  if (obj->getType() == AGameObject::CHARACTER)
    _characters.push_back(obj);
}

void  BomberMap::remove(AGameObject *obj)
{
  this->_objects.erase(obj);
  if (obj->getType() == AGameObject::CHARACTER)
    {
      std::vector<AGameObject *>::iterator	it = _characters.begin();
      while (it != _characters.end())
	{
	  if (*it == obj)
	    it = _characters.erase(it);
	  else
	    ++it;
	}
    }
}

void  BomberMap::move(AGameObject *obj, const irr::core::vector2df &pos)
{
    this->_objects[obj] = pos;
}

std::vector<AGameObject *>  BomberMap::getObjsFromVector2(const irr::core::vector2df &pos) const
{
    std::vector<AGameObject *>  objs;

    for (std::map<AGameObject*, irr::core::vector2df>::const_iterator it = this->_objects.begin(); it != this->_objects.end(); ++it) {
        if ((*it).second == pos) {
            objs.push_back((*it).first);
        }
    }
    return (objs);
}

const irr::core::vector2df  BomberMap::get(AGameObject *obj)
{
    return (this->_objects[obj]);
}

void    BomberMap::loadModel(struct model mod)
{
    irr::scene::IAnimatedMesh           *meshNode;
    irr::scene::IAnimatedMeshSceneNode  *node;

    if (!(meshNode = IrrlichtController::getSceneManager()->getMesh(mod.mesh.c_str())))
    {
        IrrlichtController::getDevice()->drop();
        throw std::runtime_error("Failed to create IAnimatedMesh in AGameObject");
    }
    else if ((node = IrrlichtController::getSceneManager()->addAnimatedMeshSceneNode(meshNode, 0, 0)))
    {
        node->setMaterialTexture(0, IrrlichtController::getDriver()->getTexture(mod.texture.c_str()));
        node->setMD2Animation(irr::scene::EMAT_STAND);
        node->setMaterialFlag(irr::video::EMF_LIGHTING ,true);
    }
}
