//

// Video.cpp for indie studio in /home/tavern_d/rendu/semestre4/cpp_indie_studio/src
// 
// Made by Matthieu Tavernier
// Login   <tavern_d@epitech.net>
// 
// Started on  Thu Apr 28 11:55:48 2016 Matthieu Tavernier
// Last update Fri Apr 29 18:53:31 2016 Victor Gouet
//

#include "Video.hpp"
#include "../include/IrrlichtController.hpp"

Video::Video(const std::string path)
{
  DIR	*rep;
  
  rep = opendir(path.data());
  if (rep != NULL)
    {
      struct dirent	*ent;

      while ((ent = readdir(rep)) != NULL)
	{
	  if (std::string(ent->d_name) != "." && std::string(ent->d_name) != "..")
	    this->files.push_back(path + "/" + std::string(ent->d_name));
	}
      closedir(rep);
      std::sort(this->files.begin(), this->files.end());
    }
}

Video::~Video()
{
}

void	Video::start()
{
  irr::IrrlichtDevice* device = IrrlichtController::getDevice();
  irr::video::IVideoDriver* driver = device->getVideoDriver();
  std::vector<irr::video::ITexture *>	frames;
  for (std::vector<std::string>::const_iterator it = this->files.begin(), end = this->files.end(); it != end; ++it)
    {
      frames.push_back(driver->getTexture((*it).data()));
    }
  irr::scene::ISceneManager *sceneManager = device->getSceneManager();
  irr::core::position2d<irr::s32> position0;
  position0.X = 0;
  position0.Y = 0;
  irr::core::position2d<irr::s32> position1;
  position1.X = IrrlichtController::width;
  position1.Y = IrrlichtController::height;
  irr::core::rect<irr::s32> rectangle;
  rectangle.UpperLeftCorner = position0;
  rectangle.LowerRightCorner = position1;
  std::vector<irr::video::ITexture *>::iterator	it = frames.begin();
  while (device->run() && it != frames.end())
    {
      driver->beginScene(true, true, irr::video::SColor(0,0,0,0));
      driver->draw2DImage(*it, position0, rectangle, 0, irr::video::SColor(255,255,255,255), true);
      driver->endScene();
      usleep(66666);
      ++it;
    }
  device->drop ();
}
