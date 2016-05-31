//
// IrrlichtController.cpp for IRRLICHT in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Tue Apr 26 21:04:22 2016 Victor Gouet
// Last update Tue May 31 11:45:58 2016 Victor Gouet
//

#include <stdexcept>
#include "../include/IrrlichtController.hpp"

// redeclare static member for cpp linkage
irr::IrrlichtDevice     *IrrlichtController::device = NULL;
size_t    IrrlichtController::width = 1920;
size_t    IrrlichtController::height = 1080;

irr::IrrlichtDevice *IrrlichtController::getDevice(bool fullScreen)
{
      if (!device)
      {
          /*Display* disp = XOpenDisplay(NULL);s
          Screen*  scrn = DefaultScreenOfDisplay(disp);
          height = scrn->height;
          width  = scrn->width;*/

          if (fullScreen)
          {
              device = irr::createDevice(irr::video::EDT_OPENGL,
                                         irr::core::dimension2d<irr::u32>(width, height), 32,
                                         true, false, false, 0);
          }
          else
          {
              /*height = 640;
              width = 640;*/
              device = irr::createDevice(irr::video::EDT_OPENGL,
                                         irr::core::dimension2d<irr::u32>(width, height), 32,
                                         false, false, false, 0);
          }
	  if (!device)
	    throw std::runtime_error("device failed !");
          device->getSceneManager()->setShadowColor(irr::video::SColor(100, 100, 100, 1));
          device->setWindowCaption(L"ONE TRYYY");
          device->getCursorControl()->setVisible(false);
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
