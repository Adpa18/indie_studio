//
// main.cpp for MAIN in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio/src
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Tue Apr 26 21:31:44 2016 Victor Gouet
// Last update Mon May  9 11:59:54 2016 Victor Gouet
//

// #include "../include/AGameObject.hpp"

// # include "../include/ACharacter.hpp"

#include "../include/GameManager.hpp"

// #include "../include/FireBomb.hpp"
// #include "../include/EventGame.hpp"
// #include "../include/Player.hpp"
// #include "../include/BomberMap.hpp"
#include <iostream>


int	main()
{
  GameManager::SharedInstance()->run();
  return (0);









  // PLUS UTILISE
  IrrlichtController::getDevice(false);
  EventGame		                eventGame;
  IrrlichtController::getDevice()->setEventReceiver(&eventGame);
  std::vector<ACharacter *>     characters;

    characters.push_back(new Player("ROGER", irr::core::vector2df(1, 1), "media/ziggs.md3", "media/ziggs.png", 0, eventGame));
    BomberMap::getMap()->genMap();


  // FREE CAM
  // irr::scene::ICameraSceneNode* camera = IrrlichtController::getSceneManager()->addCameraSceneNodeFPS(// 0,100.0f,1.2f
  // 												      );
  // camera->setPosition(irr::core::vector3df(0,0,0));


  //camera->setFarValue(42000.0f);

 //REAL CAM
  irr::scene::ICameraSceneNode* camera = IrrlichtController::getSceneManager()->addCameraSceneNode
  (0, irr::core::vector3df(0, 250, -100), irr::core::vector3df(0,5,0));

  //camera->setPosition(irr::core::vector3df(0, 100, -100));
  camera->setTarget(irr::core::vector3df(0, 0, 0));

  camera->setAutomaticCulling(irr::scene::EAC_OFF);
  camera->setFarValue(1000);
  camera->setNearValue(10);

  IrrlichtController::getSceneManager()->setAmbientLight(irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f));

  // TEXTURE DU CIEL ET GROUND
//  IrrlichtController::getSceneManager()->addSkyBoxSceneNode(IrrlichtController::getDriver()->getTexture("/home/gouet_v/Downloads/irrlicht-1.8.3/media/irrlicht2_up.jpg"),
//							    IrrlichtController::getDriver()->getTexture("/home/gouet_v/Downloads/irrlicht-1.8.3/media/irrlicht2_dn.jpg"), //dn
//							    IrrlichtController::getDriver()->getTexture("/home/gouet_v/Downloads/irrlicht-1.8.3/media/irrlicht2_lf.jpg"), //lf
//							    IrrlichtController::getDriver()->getTexture("/home/gouet_v/Downloads/irrlicht-1.8.3/media/irrlicht2_rt.jpg"), //rt
//							    IrrlichtController::getDriver()->getTexture("/home/gouet_v/Downloads/irrlicht-1.8.3/media/irrlicht2_ft.jpg"), //ft
//							    IrrlichtController::getDriver()->getTexture("/home/gouet_v/Downloads/irrlicht-1.8.3/media/irrlicht2_bk.jpg")); //bk

  while (IrrlichtController::getDevice()->run())
    {
      IrrlichtController::getDriver()->beginScene(true, true, irr::video::SColor(255,100,101,140));

      if (eventGame.IsKeyDown(irr::KEY_ESCAPE)) {
      	  break;
      }
        for (std::vector<ACharacter*>::iterator it = characters.begin(); it != characters.end(); ++it) {
            (*it)->compute();
        }
      IrrlichtController::getSceneManager()->drawAll();
      IrrlichtController::getGUIEnvironment()->drawAll();
      IrrlichtController::getDriver()->endScene();
    }
  IrrlichtController::getDevice()->drop();
}
