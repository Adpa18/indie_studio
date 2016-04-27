//
// IrrlichtController.cpp for IRRLICHT in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Tue Apr 26 21:04:22 2016 Victor Gouet
// Last update Wed Apr 27 15:20:29 2016 Victor Gouet
//

#include "../include/IrrlichtController.hpp"

// redeclare static member for cpp linkage
irr::IrrlichtDevice *IrrlichtController::device = NULL;

irr::IrrlichtDevice *IrrlichtController::getDevice()
{
  //static irr::IrrlichtDevice *device = NULL;

  if (!device)
    {
      device = irr::createDevice(irr::video::EDT_SOFTWARE,
				 irr::core::dimension2d<irr::u32>(width, height), 32,
				 false, false, false, 0);
    }
  return (device);
}


irr::video::IVideoDriver	*IrrlichtController::getDriver()
{
  return (getDevice()->getVideoDriver());
}

irr::scene::ISceneManager	*IrrlichtController::getSceneManager()
{
  return (getDevice()->getSceneManager());
}

irr::gui::IGUIEnvironment	*IrrlichtController::getGUIEnvironment()
{
  return (getDevice()->getGUIEnvironment());
}
