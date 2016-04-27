//
// main.cpp for MAIN in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio/src
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Tue Apr 26 21:31:44 2016 Victor Gouet
// Last update Wed Apr 27 15:59:42 2016 Victor Gouet
//

// #include "../include/AGameObject.hpp"

// # include "../include/ACharacter.hpp"

#include "../include/Player.hpp"
#include "../include/EventGame.hpp"
#include <iostream>


int	main()
{
  IrrlichtController::getDevice();

  EventGame		eventGame;

  IrrlichtController::getDevice()->setEventReceiver(&eventGame);

  std::map<irr::EKEY_CODE, irr::EKEY_CODE> keycodes;

  Player	sydney("ROGER", irr::core::vector3df(0, 0, 0), "media/sydney", 1// , _keycodes
		       , eventGame, keycodes);

  irr::scene::ICameraSceneNode* camera = IrrlichtController::getSceneManager()->addCameraSceneNodeFPS(0, 100.0f, .3f, 0, 0, 0, true, 3.f);//(0, irr::core::vector3df(0,30,-40), irr::core::vector3df(0,5,0));

  camera->setPosition(irr::core::vector3df(50,50,-60));
  camera->setTarget(irr::core::vector3df(-70,30,-60));


  while (IrrlichtController::getDevice()->run())
    {
      IrrlichtController::getDriver()->beginScene(true, true, irr::video::SColor(255,100,101,140));

      sydney.compute();

      IrrlichtController::getSceneManager()->drawAll();
      IrrlichtController::getGUIEnvironment()->drawAll();

      IrrlichtController::getDriver()->endScene();
    }

  IrrlichtController::getDevice()->drop();

}
