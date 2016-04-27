//
// main.cpp for MAIN in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio/src
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Tue Apr 26 21:31:44 2016 Victor Gouet
// Last update Wed Apr 27 20:17:26 2016 Victor Gouet
//

// #include "../include/AGameObject.hpp"

// # include "../include/ACharacter.hpp"

#include "../include/Player.hpp"
#include "../include/EventGame.hpp"
#include "../include/BomberMap.hpp"
#include <iostream>


int	main()
{
  IrrlichtController::getDevice();

  EventGame		eventGame;

  IrrlichtController::getDevice()->setEventReceiver(&eventGame);

  std::map<ACharacter::ACTION, irr::EKEY_CODE> keycodes = {
      {ACharacter::LEFT, irr::KEY_LEFT},
      {ACharacter::RIGHT, irr::KEY_RIGHT},
      {ACharacter::UP, irr::KEY_UP},
      {ACharacter::DOWN, irr::KEY_DOWN}
  };

  std::map<ACharacter::ACTION, irr::EKEY_CODE> keycodes2 = {
      {ACharacter::LEFT, irr::KEY_KEY_Q},
      {ACharacter::RIGHT, irr::KEY_KEY_D},
      {ACharacter::UP, irr::KEY_KEY_Z},
      {ACharacter::DOWN, irr::KEY_KEY_S}
  };

  BomberMap		map(11, 11);

  Player	sydney("ROGER", irr::core::vector3df(0, 0, 0), "media/pikachu", 1// , _keycodes
		       , eventGame, keycodes);

  Player        pikashy("ROGER", irr::core::vector3df(30, 0, 0), "media/pikachu", 1// , _keycodes
		       , eventGame, keycodes2);

  irr::scene::ICameraSceneNode* camera = IrrlichtController::getSceneManager()->addCameraSceneNode
  (0, irr::core::vector3df(0, 320
			   , 0//-250
			   ), irr::core::vector3df(0,5,0));

  //camera->setPosition(irr::core::vector3df(0, 100, -100));
  camera->setTarget(irr::core::vector3df(0, 0, 0));


  while (IrrlichtController::getDevice()->run())
    {
      IrrlichtController::getDriver()->beginScene(true, true, irr::video::SColor(255,100,101,140));

      sydney.compute();
      pikashy.compute();

      IrrlichtController::getSceneManager()->drawAll();
      IrrlichtController::getGUIEnvironment()->drawAll();

      // camera->setTarget(sydney->getPosition());

      IrrlichtController::getDriver()->endScene();
    }

  IrrlichtController::getDevice()->drop();

}
