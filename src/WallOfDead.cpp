//
// WallOfDead.cpp for WALLOFDEAD in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Jun  1 14:15:48 2016 Victor Gouet
// Last update Wed Jun  1 18:32:37 2016 Victor Gouet
//

#include <iostream>
#include "../include/WallOfDead.hpp"
#include "../include/Texture.hpp"

WallOfDead::WallOfDead(irr::core::vector2df const &pos, int timeout)
  : AGameObject(irr::core::vector2df(-3000, -3000),
		BomberManTexture::getModel("fireBomb").mesh,
		BomberManTexture::getModel("fireBomb").texture, AGameObject::OTHER, timeout),
    pos(pos)

{
}

WallOfDead::~WallOfDead()
{
}

void          WallOfDead::dead()
{
  std::cout << "call" << std::endl;
  new Explosion(pos, BomberManTexture::getModel("fire").texture, 100);
}

bool		WallOfDead::isDestructible() const
{
  return (true);
}

void		WallOfDead::updateTimeOut()
{
}

void	        WallOfDead::serialize(irr::io::IXMLWriter *) const
{
}

void		WallOfDead::createWallOfDead(int size, double appearAtTime)
{
  double	i;
  int		pos;

  i = appearAtTime;
  pos = 1;
  while (pos < size / 2)
    {
      for (int y = pos; y < size - pos - 1 ; ++y)
      	{
      	  new WallOfDead(irr::core::vector2df(y, pos), i);
      	  ++i;
      	}

      for (int y = pos; y < size - 1 - pos ; ++y)
      	{
      	  new WallOfDead(irr::core::vector2df(size - 1 - pos, y), i);
      	  ++i;
      	}

      for (int y = size - 1 - pos; y > pos ; --y)
      	{
      	  new WallOfDead(irr::core::vector2df(y, size - 1 - pos), i);
      	  ++i;
      	}

      for (int y = size - 1 - pos; y > pos ; --y)
      	{
      	  new WallOfDead(irr::core::vector2df(pos, y), i);
      	  ++i;
      	}

      ++pos;
    }
}
