//
// WallOfDead.cpp for WALLOFDEAD in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Jun  1 14:15:48 2016 Victor Gouet
// Last update Wed Jun  1 20:03:08 2016 Victor Gouet
//

#include <iostream>
#include "../include/WallOfDead.hpp"
#include "../include/Texture.hpp"
#include "../include/BomberMap.hpp"

const double	WallOfDead::timerSpawn = 1;

WallOfDead::WallOfDead(double timeout)
{
  struct tm	y2k;
  time_t	timer;
  
  timer = time(NULL);
  memset(&y2k, 0, sizeof(y2k));
  y2k.tm_year = 100;
  y2k.tm_mday = 1;
  _beginTimer = difftime(timer, mktime(&y2k));
  _timeOut = timeout;
  _pos = 1;
  resetPos();
}

WallOfDead::~WallOfDead()
{
}

void		WallOfDead::resetPos()
{
  _y1 = _pos;
  _y2 = _pos;
  _y3 = BomberMap::getMap()->getSize() - 1 - _pos;
  _y4 = BomberMap::getMap()->getSize() - 1 - _pos;
}

void		WallOfDead::createWallOfDead()
{
  int		size = BomberMap::getMap()->getSize();

  if (_y1 < size - _pos - 1)
    {
      new Explosion(irr::core::vector2df(_y1, _pos),
		    BomberManTexture::getModel("fire").texture, 100);
      ++_y1;
    }
  else if (_y2 < size - 1 - _pos)
    {
      new Explosion(irr::core::vector2df(size - 1 - _pos, _y2),
		    BomberManTexture::getModel("fire").texture, 100);
      ++_y2;
    }
  else if (_y3 > _pos)
    {
      new Explosion(irr::core::vector2df(_y3, size - 1 - _pos),
		    BomberManTexture::getModel("fire").texture, 100);
      --_y3;
    }

  else if (_y4 > _pos)
    {
      new Explosion(irr::core::vector2df(_pos, _y4),
		    BomberManTexture::getModel("fire").texture, 100);
      --_y4;
    }

  if (_y1 == size - _pos - 1 && _y2 == size - 1 - _pos && _y3 == _pos && _y4 == _pos)
    {
      resetPos();
      _pos = _pos + WallOfDead::timerSpawn;
    }
}

bool		WallOfDead::canDropWall() const
{
  time_t	timer;
  struct tm	y2k;
  double	seconds;

  timer = time(NULL);
  memset(&y2k, 0, sizeof(y2k));
  y2k.tm_year = 100;
  y2k.tm_mday = 1;
  seconds = difftime(timer, mktime(&y2k));
  if ((seconds - _beginTimer) > _timeOut)
    {
      _timeOut += 1;
      return (true);
    }
  return (false);
}
