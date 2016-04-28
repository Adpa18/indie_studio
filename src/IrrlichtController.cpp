//
// IrrlichtController.cpp for IRRLICHT in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Tue Apr 26 21:04:22 2016 Victor Gouet
// Last update Thu Apr 28 11:20:34 2016 Victor Gouet
//

#include "../include/IrrlichtController.hpp"

// redeclare static member for cpp linkage
irr::IrrlichtDevice *IrrlichtController::device = NULL;
size_t    IrrlichtController::width = 1920;
size_t    IrrlichtController::height = 1080;

irr::IrrlichtDevice *IrrlichtController::getDevice()
{
  if (!device)
    {
      Display* disp = XOpenDisplay(NULL);
      Screen*  scrn = DefaultScreenOfDisplay(disp);
      height = scrn->height;
      width  = scrn->width;

      // irr::createDevice(video::E_DRIVER_TYPE deviceType, const core::dimension2d<u32> &windowSize, u32 bits, , bool stencilbuffer, bool vsync, irr::IEventReceiver *receiver)
      device = irr::createDevice(irr::video::EDT_BURNINGSVIDEO,
				 irr::core::dimension2d<irr::u32>(width, height), 32,
				 true, false, false, 0);
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

irr::scene::ISceneCollisionManager  *IrrlichtController::getSceneCollisionManager()
{
  return (getSceneManager()->getSceneCollisionManager());
}
