//
// IrrlichtController.hpp for IRRLICHT in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Tue Apr 26 21:04:35 2016 Victor Gouet
// Last update Fri Apr 29 10:08:51 2016 Victor Gouet
//

#ifndef IRRLICHTCONTROLLER_HPP_
# define IRRLICHTCONTROLLER_HPP_

//# include <X11/Xlib.h>
# include "../Irrlicht/irrlicht-1.8.3/include/irrlicht.h"
# include <map>

class AGameObject;

class	IrrlichtController
{
public:
    static size_t    width;
    static size_t    height;
  static irr::IrrlichtDevice                *getDevice(bool pleinSceen = true);
  static irr::video::IVideoDriver           *getDriver();
  static irr::scene::ISceneManager          *getSceneManager();
  static irr::gui::IGUIEnvironment          *getGUIEnvironment();
  static irr::scene::ISceneCollisionManager *getSceneCollisionManager();

private:
    static irr::IrrlichtDevice *device;
public:
    static const size_t	bombSize = 15;
};

#endif
