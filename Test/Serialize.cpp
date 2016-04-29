//
// Created by gaspar_q on 4/27/16.
//

#include <map>
#include <irrlicht.h>
#include <AGameObject.hpp>
#include <Player.hpp>
#include <iostream>
#include <unistd.h>

namespace MapOfBomberman
{
    std::vector<AGameObject *>	_objects;

    void    serialize(std::string const &saveFile)
    {
        irr::IrrlichtDevice  *device = IrrlichtController::getDevice();
        irr::io::IAttributes *attributes;
        irr::io::IXMLWriter *writter;

        writter = device->getFileSystem()->createXMLWriter(saveFile.c_str());
        writter->writeXMLHeader();
        writter->writeElement(L"Map");
        writter->writeLineBreak();
        for (std::vector<AGameObject *>::iterator it = _objects.begin(), end = _objects.end(); it != end; ++it)
        {
            attributes = device->getFileSystem()->createEmptyAttributes();
            (**it)->serializeAttributes(attributes);
            attributes->write(writter, false, L"attributes");
            delete(attributes);
        }
        writter->writeClosingTag(L"Map");
        writter->drop();
    }

    void  deserialize(std::string const &loadFile)
    {
        irr::IrrlichtDevice *device = IrrlichtController::getDevice();
        irr::io::IAttributes *attributes;
        irr::io::IXMLReader *reader;
        EventGame   eventGame;
        std::map<ACharacter::ACTION, irr::EKEY_CODE> keycodes;
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
                toPush = new Player("Richard", irr::core::vector3df(0, 0, 0), "../media/pikachu", 42, eventGame, keycodes);
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
}

int main()
{
  IrrlichtController::getDevice(false);

   EventGame   eventGame;std::map<ACharacter::ACTION, irr::EKEY_CODE> keycodes;
   MapOfBomberman::_objects.push_back(new Player("Richard", irr::core::vector3df(5, 0, 0), "../media/pikachu", 42, eventGame, keycodes));
   MapOfBomberman::_objects.push_back(new Player("Simon", irr::core::vector3df(15, 0, 0), "../media/pokeball", 42, eventGame, keycodes));
   MapOfBomberman::_objects.push_back(new Player("Jean-Louis", irr::core::vector3df(25, 0, 0), "../media/salameche", 42, eventGame, keycodes));
   MapOfBomberman::_objects.push_back(new Player("Albert", irr::core::vector3df(35, 0, 0), "../media/carapuce", 42, eventGame, keycodes));
   MapOfBomberman::_objects.push_back(new Player("Irrlicht", irr::core::vector3df(45, 0, 0), "../media/bulbizarre", 42, eventGame, keycodes));
//
   MapOfBomberman::serialize("toto.xml");
//
    // MapOfBomberman::deserialize("toto.xml");

    // for (std::vector<AGameObject *>::iterator it = MapOfBomberman::_objects.begin(), end = MapOfBomberman::_objects.end(); it != end; ++it)
    // {
    //     std::cout << (*it)->operator->()->getPosition().X << ", " << (*it)->operator->()->getPosition().Y << ", " << (*it)->operator->()->getPosition().Z << std::endl;
    //     std::cout << (*it)->operator->()->getName() << std::endl;
    //     delete(*it);
    // }
//    irr::scene::ISceneManager *manager = IrrlichtController::getSceneManager();
//    irr::video::IVideoDriver *driver = IrrlichtController::getDriver();
//    irr::scene::ICameraSceneNode* camera = IrrlichtController::getSceneManager()->addCameraSceneNode(0, irr::core::vector3df(0, 320, -250), irr::core::vector3df(0,5,0));

//    irr::io::IAttributes *out;
//    irr::io::SAttributeReadWriteOptions options;
//    irr::io::IXMLWriter *towrite;
//
//    towrite = device->getFileSystem()->createXMLWriter(L"toto.xml");
//    out = device->getFileSystem()->createEmptyAttributes();
//
//    towrite->writeXMLHeader();
//
//    towrite->writeElement(L"toto");
//    towrite->writeLineBreak();
//
//    towrite->writeElement(L"tutu");
//    towrite->writeLineBreak();
//
//    options.Filename = "tutu";
//    (*object)->serializeAttributes(out, NULL);
//    out->write(towrite, false, L"Object");
//
//    towrite->writeClosingTag(L"tutu");
//    towrite->writeLineBreak();
//
//    towrite->writeClosingTag(L"toto");
//    towrite->writeLineBreak();
//
//    towrite->drop();
//
//    irr::io::IXMLReader *toRead;
//toRead = device->getFileSystem()->createXMLReader("toto.xml");
//
//    toRead->read();
//
//    std::cout << "att count: " << toRead->getAttributeCount() << std::endl;
//    for (size_t i = 0, len = toRead->getAttributeCount(); i < len; ++i)
//    {
//        std::cout << "att name[" << i << "]: " << toRead->getAttributeName(static_cast<int>(i)) << std::endl;
//        std::cout << toRead->getAttributeValue(static_cast<int>(i))<< std::endl;
//    }
//    toRead->drop();

//    while (device->run())
//    {
//        if (device->isWindowActive())
//        {
//            driver->beginScene(true, true, irr::video::SColor(255,200,200,200));
//            manager->drawAll();
//            driver->endScene();
//        }
//        else
//            device->yield();
//    }

    return (0);
}
