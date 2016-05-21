//
// BomberMap.cpp for MAP in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 18:14:09 2016 Victor Gouet
// Last update Sat May 21 11:40:08 2016 Victor Gouet
//

#include <cstdlib>
#include <iostream>
#include "irrXML.h"
#include "../include/BomberMap.hpp"
#include "../include/Texture.hpp"
#include "../include/Color.hpp"
//#include "../include/Player.hpp"

BomberMap *BomberMap::bomberMap = NULL;

const int		BomberMap::size_side[3] = {9, 13, 15};

BomberMap::BomberMap(std::string const &filename) : _mapSize(SMALL), _filename(filename)
{
}

BomberMap::BomberMap(Size mapSize) : _mapSize(mapSize), _filename("")
{
  terrain_model = NULL;
   _camera = NULL;
  initSpawn();
}

BomberMap::~BomberMap()
{
  std::map<AGameObject*, irr::core::vector2df>::iterator it_o = _objects.begin();
  while (it_o != _objects.end())
    {
      AGameObject	*obj = (*it_o).first;
      delete (obj);
      it_o = _objects.begin();
    }

  for (std::vector<irr::scene::ILightSceneNode*>::iterator it = lightVector.begin(), end = lightVector.end() ; end != it ; ++it)
    {
      (*it)->remove();
    }
}

void            BomberMap::genMap()
{
    this->generateMap();
    // this->generateGround();
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
	{
	  new Wall(irr::core::vector2df(x, y), Wall::Edge);
	}
      else if (x % 2 == 0 && y % 2 == 0 && x != 0 && y != 0)
	{
	  int dice = rand() % 3;
	  new Wall(irr::core::vector2df(x, y), Wall::Invicible, _walls[dice].first, _walls[dice].second);
	}
      else if (canPutDestructibleWall(x, y))
	{
	  new Wall(irr::core::vector2df(x, y));
	}
    }
  }
}

// void BomberMap::serialize(const std::string &saveFile) const
// {
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
// }

void rotate(irr::scene::ISceneNode *node, irr::core::vector3df rot)
{
   irr::core::matrix4 m;
   m.setRotationDegrees(node->getRotation());
   irr::core::matrix4 n;
   n.setRotationDegrees(rot);
   m *= n;
   node->setRotation( m.getRotationDegrees() );
   node->updateAbsolutePosition();
}

//--- turn ship left or right ---
void turn(irr::scene::ISceneNode *node, irr::f32 rot)
{
   rotate(node, irr::core::vector3df(0.0f, rot, 0.0f) );
}

//--- pitch ship up or down ---
void pitch(irr::scene::ISceneNode *node, irr::f32 rot)
{
   rotate(node, irr::core::vector3df(rot, 0.0f, 0.0f) );
}

//--- roll ship left or right ---
void roll(irr::scene::ISceneNode *node, irr::f32 rot)
{
   rotate(node, irr::core::vector3df(0.0f, 0.0f, rot) );
}

irr::scene::ICameraSceneNode *BomberMap::get_camera() const {
   return _camera;
}

void BomberMap::deserialize()
{
   //irr::IrrlichtDevice *device = IrrlichtController::getDevice();
   irr::io::IrrXMLReader *reader;
   int initAsset;
   bool initCam;
   bool initTarget;
   //irr::io::IAttributes *attributes;
   //EventGame   eventGame;
   //AGameObject *toPush;
   //irr::core::stringw mapelem(L"attributes");
   reader = irr::io::createIrrXMLReader(_filename.c_str());
   initAsset = 0;
   initCam = false;
   initTarget = false;
   std::string nodeName;
   std::string meshesDir;
   std::string texturesDir;
   while (reader && reader->read())
   {
     if (reader->getNodeType() == irr::io::EXN_ELEMENT)
     {
        nodeName = (char *) reader->getNodeName();
        if (!initTarget && nodeName == "target")
        {
           _target.X = reader->getAttributeValueAsFloat("px");
           _target.Y = reader->getAttributeValueAsFloat("py");
           _target.Z = reader->getAttributeValueAsFloat("pz");
           initTarget = true;
        }
        if (initTarget && !initCam && nodeName == "camera")
        {
           _camera_pos.X = reader->getAttributeValueAsFloat("px");
           _camera_pos.Y = reader->getAttributeValueAsFloat("py");
           _camera_pos.Z = reader->getAttributeValueAsFloat("pz");
           _camera = IrrlichtController::getSceneManager()->addCameraSceneNode(0, _camera_pos);
           _camera->setAspectRatio(19/9);
           _camera->setFOV(reader->getAttributeValueAsFloat("fov"));
           //_camera->setScale(irr::core::vector3df(1,1,1));
           _camera->setTarget(_target);
           _camera->setAutomaticCulling(irr::scene::EAC_OFF);
           _camera->setFarValue(1000);
           _camera->setNearValue(10);
           initCam = true;
        }
        else if (nodeName == "size")
        {
            _mapSize = (Size) reader->getAttributeValueAsInt("size");
        }
        else if (nodeName == "spawn")
        {
           _spawner.push_back(irr::core::vector2df(reader->getAttributeValueAsFloat("px"), reader->getAttributeValueAsFloat("py")));
        }
        else if (nodeName == "ambient_light")
        {
           IrrlichtController::getSceneManager()->setAmbientLight(irr::video::SColorf(reader->getAttributeValueAsFloat("r"),
                                                                                      reader->getAttributeValueAsFloat("g"),
                                                                                      reader->getAttributeValueAsFloat("b"),
                                                                                      reader->getAttributeValueAsFloat("a")));
        }
        else if (nodeName == "light")
        {
           irr::scene::ILightSceneNode*   light;
           irr::video::SLight             light_data;

           nodeName = reader->getAttributeValueSafe("type");
           if (nodeName == "spot")
              light_data.Type = irr::video::ELT_SPOT;
           else if (nodeName == "point")
              light_data.Type = irr::video::ELT_POINT;
           else if (nodeName == "directional")
              light_data.Type = irr::video::ELT_DIRECTIONAL;
           light_data.Radius = reader->getAttributeValueAsFloat("radius");
           light_data.OuterCone = reader->getAttributeValueAsFloat("outer_cone");
           Color col(reader->getAttributeValueSafe("ambient_color"));
           light_data.AmbientColor = irr::video::SColorf(col.r, col.g, col.b);
           col.set(reader->getAttributeValueSafe("specular_color"));
           light_data.SpecularColor = irr::video::SColorf(col.r, col.g, col.b, col.a);
           col.set(reader->getAttributeValueSafe("diffuse_color"));
           light_data.DiffuseColor = irr::video::SColorf(col.r, col.g, col.b, col.a);

           light = IrrlichtController::getSceneManager()->addLightSceneNode();
           light->setLightData(light_data);
           light->setRadius(reader->getAttributeValueAsFloat("radius"));
           light->enableCastShadow(false);
           light->setPosition(irr::core::vector3df(reader->getAttributeValueAsFloat("px"),
                                                   reader->getAttributeValueAsFloat("py"),
                                                   reader->getAttributeValueAsFloat("pz")));
           light->setRotation(irr::core::vector3df(reader->getAttributeValueAsFloat("rx"),
                                                   reader->getAttributeValueAsFloat("ry"),
                                                   reader->getAttributeValueAsFloat("rz")));

           //light->setVisible(true);
        }
        else if (nodeName == "meshes_dir")
        {
           meshesDir = reader->getAttributeValueSafe("file");
           initAsset += 1;
        }
        else if (nodeName == "textures_dir")
        {
           texturesDir = reader->getAttributeValueSafe("file");
           initAsset += 1;
        }
        else if (initAsset == 2 && nodeName == "props")
        {
           float repeat = reader->getAttributeValueAsFloat("repeat");
           _props.push_back(new Props(meshesDir + std::string(reader->getAttributeValueSafe("mesh")),
                                      texturesDir + std::string(reader->getAttributeValueSafe("texture")),
                                      irr::core::vector2df(repeat, repeat),
                                      reader->getAttributeValueAsInt("transparent")));
        }
        else if (nodeName == "walls")
        {
           _walls[0].first = meshesDir + reader->getAttributeValueSafe("mesh1");
           _walls[0].second = texturesDir + reader->getAttributeValueSafe("texture1");
           _walls[1].first = meshesDir + reader->getAttributeValueSafe("mesh2");
           _walls[1].second = texturesDir + reader->getAttributeValueSafe("texture2");
           _walls[2].first = meshesDir + reader->getAttributeValueSafe("mesh3");
           _walls[2].second = texturesDir + reader->getAttributeValueSafe("texture3");
        }
     }
      //  if (reader->getNodeType() == irr::io::EXN_ELEMENT && mapelem.equals_ignore_case(reader->getNodeName()))
      //  {
      //      Player  *character;
       //
      //      attributes = device->getFileSystem()->createEmptyAttributes();
      //      attributes->read(reader, true);
      //      toPush = new Player("Richard", irr::core::vector3df(0, 0, 0), "../media/pikachu.md2", "../media/pikachu.png", 42, eventGame);
      //      (*toPush)->deserializeAttributes(attributes);
      //      character = dynamic_cast<Player *>(toPush);
      //      if (character != NULL)
      //          character->setName((*toPush)->getName());
      //      _objects.push_back(toPush);
      //      attributes->drop();
      //  }
   }
   delete reader;
}

void		BomberMap::refreshCamera()
{
   _camera->setPosition(_camera_pos);
   _camera->setTarget(_target);
}

void		BomberMap::newMap(Size mapSize)
{
  if (bomberMap)
    {
      delete bomberMap;
    }
  bomberMap = new BomberMap(mapSize);
}

void		BomberMap::newMap(std::string const& filename)
{
   if (bomberMap)
   {
      delete bomberMap;
   }
   bomberMap = new BomberMap(filename);
   bomberMap->deserialize();
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
