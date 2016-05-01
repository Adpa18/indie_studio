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
    static const size_t	scale = 25;
    enum Direction {
        LEFT = 1 << 0,
        RIGHT = 1 << 1,
        UP = 1 << 2,
        DOWN = 1 << 3
    };
    enum Controller {
        SQUARE = 1 << 0,
        CROSS = 1 << 1,
        CIRCLE = 1 << 2,
        TRIANGLE = 1 << 3,
        L1 = 1 << 4,
        R1 = 1 << 5,
        L2 = 1 << 6,
        R2 = 1 << 7,
        FIRST_OPTION = 1 << 7,
        SECOND_OPTION = 1 << 8,
        L3 = 1 << 9,
        R3 = 1 << 10,
        HOME = 1 << 11,
        OTHER = 1 << 12
    };
};

#endif
