//
// WallOfDead.cpp for WALLOFDEAD in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Jun  1 14:15:48 2016 Victor Gouet
// Last update Wed Jun  1 15:35:10 2016 Victor Gouet
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

void		WallOfDead::createWallOfDead(int size)
{
  double	i;

  i = 4;
  for (int x = 0; x < size ; ++x)
    {
      for (int y = 0; y < size ; ++y)
  	{
  	  new WallOfDead(irr::core::vector2df(x, y), i);
  	  i = i + 1;
  	}
    }
}
