//
// main.cpp for MAIN in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio/src
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Tue Apr 26 21:31:44 2016 Victor Gouet
// Last update Thu Apr 28 11:53:45 2016 Victor Gouet
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

  BomberMap		map;

  Player	sydney("ROGER", irr::core::vector3df(-100, 0, -100), "media/pikachu", 1// , _keycodes
		       , eventGame, keycodes);

  sydney->setScale(irr::core::vector3df(1.5, 1.5, 1.5));

  Player        pikashy("ROGER", irr::core::vector3df(30, 0, 0), "media/pikachu", 1// , _keycodes
		       , eventGame, keycodes2);

  pikashy->setScale(irr::core::vector3df(1.5, 1.5, 1.5));

  // irr::scene::ICameraSceneNode* camera = IrrlichtController::getSceneManager()->addCameraSceneNodeMaya();

  // irr::scene::ICameraSceneNode* camera = IrrlichtController::getSceneManager()->addCameraSceneNodeFPS(0, 100.0f, .3f, 0, 0, 0, true, 3.f);



  // FREE CAM
  // irr::scene::ICameraSceneNode* camera = IrrlichtController::getSceneManager()->addCameraSceneNodeFPS(// 0,100.0f,1.2f
  // 												      );
  // camera->setPosition(irr::core::vector3df(0,0,0));


  //camera->setFarValue(42000.0f);

 //REAL CAM
  irr::scene::ICameraSceneNode* camera = IrrlichtController::getSceneManager()->addCameraSceneNode
  (0, irr::core::vector3df(0, 200
  			   , -200
  			   ), irr::core::vector3df(0,5,0));

  //camera->setPosition(irr::core::vector3df(0, 100, -100));
  camera->setTarget(irr::core::vector3df(0, 0, 0));

  camera->setAutomaticCulling(irr::scene::EAC_OFF);
  camera->setFarValue(2000);
  camera->setNearValue(100);

  IrrlichtController::getSceneManager()->setAmbientLight(irr::video::SColorf(1.0f, 1.0f,
									     1.0f, 1.0f));

  while (IrrlichtController::getDevice()->run())
    {
      IrrlichtController::getDriver()->beginScene(true, true, irr::video::SColor(255,100,101,140));

      if (eventGame.IsKeyDown(irr::KEY_ESCAPE))
	{
	  break;
	}

      sydney.compute();
    //   pikashy.compute();

      IrrlichtController::getSceneManager()->drawAll();
      IrrlichtController::getGUIEnvironment()->drawAll();

      // camera->setTarget(sydney->getPosition());

      IrrlichtController::getDriver()->endScene();
    }

  IrrlichtController::getDevice()->drop();

}
