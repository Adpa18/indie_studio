//
// BomberMap.cpp for MAP in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 18:14:09 2016 Victor Gouet
// Last update Tue May 10 22:26:57 2016 Victor Gouet
//

#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include "../include/BomberMap.hpp"
#include "../include/Texture.hpp"

BomberMap *BomberMap::bomberMap = NULL;

BomberMap::BomberMap(std::string const &)
{

}

BomberMap::BomberMap()
{

}

void            BomberMap::genMap()
{
    this->generateMap();
    this->generateGround();
}

void			BomberMap::generateGround()
{
    irr::scene::IAnimatedMesh *terrain_model;

    terrain_model = IrrlichtController::getSceneManager()->addHillPlaneMesh("ground",
    irr::core::dimension2d<irr::f32>(25, 25), // Tile size
    irr::core::dimension2d<irr::u32>(11, 11), // Tile count
            0, // Material
            0.0f, // Hill height
    irr::core::dimension2d<irr::f32>(0.0f, 0.0f), // countHills
    irr::core::dimension2d<irr::f32>(11, 11)); // textureRepeatCount

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
//    anim = IrrlichtController::getSceneManager()->createFlyCircleAnimator(irr::core::vector3df(0, 100, 0), 250.0f);
//    light->addAnimator(anim);

     light = IrrlichtController::getSceneManager()->addLightSceneNode();
 //    light_data.DiffuseColor = irr::video::SColorf(1.0f, 0.0f, 0.0f);
     light->setLightData(light_data);
     light->setPosition(irr::core::vector3df(125, 0, -125));
     light->setRotation(irr::core::vector3df(-45, -45, 0));
 //    anim = IrrlichtController::getSceneManager()->createFlyCircleAnimator(irr::core::vector3df(125, 0, -125), 50.0f);
 //    light->addAnimator(anim);

     light = IrrlichtController::getSceneManager()->addLightSceneNode();
 //    light_data.DiffuseColor = irr::video::SColorf(1.0f, 1.0f, 0.0f);
     light->setLightData(light_data);
     light->setPosition(irr::core::vector3df(125, 0, 125));
     light->setRotation(irr::core::vector3df(-45, 225, 0));
 //    anim = IrrlichtController::getSceneManager()->createFlyCircleAnimator(irr::core::vector3df(125, 0, 125), 50.0f);
 //    light->addAnimator(anim);

     light = IrrlichtController::getSceneManager()->addLightSceneNode();
 //    light_data.DiffuseColor = irr::video::SColorf(0.0f, 1.0f, 0.0f);
     light->setLightData(light_data);
     light->setPosition(irr::core::vector3df(-125, 0, -125));
     light->setRotation(irr::core::vector3df(-45, 45, 0));
 //    anim = IrrlichtController::getSceneManager()->createFlyCircleAnimator(irr::core::vector3df(-125, 0, -125), 50.0f);
 //    light->addAnimator(anim);

     light = IrrlichtController::getSceneManager()->addLightSceneNode();
 //    light_data.DiffuseColor = irr::video::SColorf(0.0f, 0.0f, 1.0f);
     light->setLightData(light_data);
     light->setPosition(irr::core::vector3df(-125, 0, 125));
     light->setRotation(irr::core::vector3df(-45, 135, 0));
 //    anim = IrrlichtController::getSceneManager()->createFlyCircleAnimator(irr::core::vector3df(-125, 0, 125), 50.0f);
 //    light->addAnimator(anim);

//    anim->drop();
}

void			BomberMap::generateMap()
{
  srand(time(NULL));
    for (int y = 0; y < BomberMap::size_side; ++y) {
        for (int x = 0; x < BomberMap::size_side; ++x) {
            switch (_patron[y][x]) {
                case 'E':
                    new Wall(irr::core::vector2df(x, y), Wall::Edge);
                    break;
                case 'X':
                    new Wall(irr::core::vector2df(x, y), Wall::Invicible);
                    break;
                case 'C':
                    new Wall(irr::core::vector2df(x, y));
                    break;
                default:
                    break;
            }
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

BomberMap       * BomberMap::getMap()
{
    if (!bomberMap) {
        bomberMap = new BomberMap();
    }
    return (bomberMap);
}

void  BomberMap::add(AGameObject* obj, const irr::core::vector2df &pos)
{
  this->_objects[obj] = pos;
}

void  BomberMap::remove(AGameObject *obj)
{
    this->_objects.erase(obj);
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
