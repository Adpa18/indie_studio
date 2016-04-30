//
// main.cpp for MAIN in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio/src
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Tue Apr 26 21:31:44 2016 Victor Gouet
// Last update Sat Apr 30 14:35:45 2016 Victor Gouet
//

// #include "../include/AGameObject.hpp"

// # include "../include/ACharacter.hpp"

#include "../include/Player.hpp"
#include "../include/EventGame.hpp"
#include "../include/BomberMap.hpp"
#include "../include/FireBomb.hpp"
#include <iostream>


int	main()
{
  IrrlichtController::getDevice(false);

  EventGame		eventGame;

  IrrlichtController::getDevice()->setEventReceiver(&eventGame);

  BomberMap		map;

  Player	sydney("ROGER", irr::core::vector3df(-100, 0, -100), "media/pika.md3", "media/pikachu.png", 0, eventGame);

  sydney->setScale(irr::core::vector3df(1.5, 1.5, 1.5));

  // Player        pikashy("ROGER", irr::core::vector3df(30, 0, 0), "media/pikachu", 1// , _keycodes
  // 		       , eventGame, keycodes2);

  // pikashy->setScale(irr::core::vector3df(1.5, 1.5, 1.5));

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
  camera->setFarValue(1000);
  camera->setNearValue(10);

  IrrlichtController::getSceneManager()->setAmbientLight(irr::video::SColorf(1.0f, 1.0f,
									     1.0f, 1.0f));

  // TEXTURE DU CIEL ET GROUND
  IrrlichtController::getSceneManager()->addSkyBoxSceneNode(IrrlichtController::getDriver()->getTexture("/home/gouet_v/Downloads/irrlicht-1.8.3/media/irrlicht2_up.jpg"),
							    IrrlichtController::getDriver()->getTexture("/home/gouet_v/Downloads/irrlicht-1.8.3/media/irrlicht2_dn.jpg"), //dn
							    IrrlichtController::getDriver()->getTexture("/home/gouet_v/Downloads/irrlicht-1.8.3/media/irrlicht2_lf.jpg"), //lf
							    IrrlichtController::getDriver()->getTexture("/home/gouet_v/Downloads/irrlicht-1.8.3/media/irrlicht2_rt.jpg"), //rt
							    IrrlichtController::getDriver()->getTexture("/home/gouet_v/Downloads/irrlicht-1.8.3/media/irrlicht2_ft.jpg"), //ft
							    IrrlichtController::getDriver()->getTexture("/home/gouet_v/Downloads/irrlicht-1.8.3/media/irrlicht2_bk.jpg")); //bk

  while (IrrlichtController::getDevice()->run())
    {
      IrrlichtController::getDriver()->beginScene(true, true, irr::video::SColor(255,100,101,140));

      if (eventGame.IsKeyDown(irr::KEY_ESCAPE))
      	{
      	  break;
      	}
      // else if (eventGame.IsKeyDown(irr::KEY_SPACE))
      // 	{
	  // sydney.
      // 	  std::cout << "POSSSS" << std::endl;
      // 	  if (!bomb.isUse())
      // 	    bomb << sydney->getPosition();
      	// }
      sydney.compute();
      // pikashy.compute();

      IrrlichtController::getSceneManager()->drawAll();
      IrrlichtController::getGUIEnvironment()->drawAll();

      // camera->setTarget(sydney->getPosition());

      IrrlichtController::getDriver()->endScene();
    }

  IrrlichtController::getDevice()->drop();

}
