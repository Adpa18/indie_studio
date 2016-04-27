//
// IrrlichtController.hpp for IRRLICHT in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Tue Apr 26 21:04:35 2016 Victor Gouet
// Last update Tue Apr 26 21:18:19 2016 Victor Gouet
//

#ifndef IRRLICHTCONTROLLER_HPP_
# define IRRLICHTCONTROLLER_HPP_

# include "../Irrlicht/irrlicht-1.8.3/include/irrlicht.h"

class	IrrlichtController
{
public:
    static const size_t    width = 640;
    static const size_t    height = 480;
  static irr::IrrlichtDevice		*getDevice();
  static irr::video::IVideoDriver	*getDriver();
  static irr::scene::ISceneManager	*getSceneManager();
  static irr::gui::IGUIEnvironment	*getGUIEnvironment();
};

#endif
