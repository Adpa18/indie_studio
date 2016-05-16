//
// Video.cpp for indie studio in /home/tavern_d/rendu/semestre4/cpp_indie_studio/src
//
// Made by Matthieu Tavernier
// Login   <tavern_d@epitech.net>
//
// Started on  Thu Apr 28 11:55:48 2016 Matthieu Tavernier
// Last update Mon May 16 17:43:15 2016 Fernand Veyrier
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
  irrklang::ISoundEngine *engine = irrklang::createIrrKlangDevice();
  if (!engine)
    return;
  IrrlichtController::width = 1920;
  IrrlichtController::height = 1080;
  irr::IrrlichtDevice* device = IrrlichtController::getDevice();
  irr::video::IVideoDriver* driver = device->getVideoDriver();
  std::vector<irr::video::ITexture *> frames;
  for (std::vector<std::string>::const_iterator it = this->files.begin(); it != this->files.end(); ++it)
    frames.push_back(driver->getTexture((*it).data()));
  irr::scene::ISceneManager *sceneManager = device->getSceneManager();
  irr::core::position2d<irr::s32> position0;
  position0.X = 0;
  position0.Y = 0;
  //std::vector<std::string>::const_iterator it = this->files.begin();
  clock_t	timerFrame;
  //irr::video::ITexture	*frame;
  int	i = 0;
  std::vector<irr::video::ITexture *>::iterator it = frames.begin();
  while (device->run() && it != this->files.end())
    {
      timerFrame = clock();
      frames = driver->getTexture((*it).data());
      driver->beginScene(true, true, irr::video::SColor(0,0,0,0));
      driver->draw2DImage(*it, position0);
      driver->endScene();
      if (i == 32)
  	engine->play2D("../intro/intro.wav", true);
      timerFrame = clock() - timerFrame;
      if (static_cast<float>(timerFrame) / CLOCKS_PER_SEC < 1.0 / 23.975)
  	usleep(1000000.0 / 23.975 - static_cast<float>(timerFrame) / CLOCKS_PER_SEC * 1000000.0);
      ++it;
      ++i;
    }
  engine->drop();
  device->drop();
}
