//
// main.cpp for MAIN in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio/src
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Tue Apr 26 21:31:44 2016 Victor Gouet
// Last update Tue Apr 26 22:01:29 2016 Victor Gouet
//

#include "../include/AGameObject.hpp"

int	main()
{
  IrrlichtController::getDevice();

  AGameObject	sydney(irr::core::vector3df(0, 0, 0), "media/sydney");

  IrrlichtController::getSceneManager()->addCameraSceneNode(0, irr::core::vector3df(0,30,-40), irr::core::vector3df(0,5,0));

  while (IrrlichtController::getDevice()->run())
    {
      IrrlichtController::getDriver()->beginScene(true, true, irr::video::SColor(255,100,101,140));

      sydney->setPosition(sydney->getPosition() + 0.01);

      IrrlichtController::getSceneManager()->drawAll();
      IrrlichtController::getGUIEnvironment()->drawAll();

      IrrlichtController::getDriver()->endScene();
    }

  IrrlichtController::getDevice()->drop();
    
}
