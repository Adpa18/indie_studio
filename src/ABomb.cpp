//
// Bomb.cpp for BOMB in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Thu Apr 28 16:25:11 2016 Victor Gouet
// Last update Wed May 11 16:36:38 2016 Victor Gouet
//

#include <iostream>
#include <unistd.h>
#include "../include/ABomb.hpp"
#include "../include/BombFactory.hpp"

ABomb::ABomb(std::string const &mesh, std::string const &texture) :
  AGameObject(irr::core::vector2df(-1000, -1000),
	      mesh, texture, AGameObject::BOMB),
  mesh(mesh), texture(texture)
{
  use = false;
  (*this)->setVisible(false);
  _power = 3;
  __active = false;
}

ABomb::ABomb(ABomb const *other)
  : AGameObject(irr::core::vector2df(-1000, -1000),
		other->mesh,
		other->texture, AGameObject::BOMB)
{
  *this = other;
}

ABomb	&ABomb::operator=(ABomb const *other)
{
  use = false;
  (*this)->setVisible(false);
  this->_power = other->_power;
  this->__active = false;
  this->mesh = other->mesh;
  this->texture = other->texture;
  return (*this);
}

ABomb::~ABomb()
{
}

void                        ABomb::dead()
{
  
  if (use)
    {
      use = false;
      willExplose();
      disable();
    }
}

bool				ABomb::isDestructible() const
{
  return (false);
}

bool			ABomb::isUse() const
{
  return (use);
}

void		ABomb::disable()
{
  this->setPos(irr::core::vector2df(-1000, -1000));
}

void			ABomb::operator<<(irr::core::vector2df
					  const &pos)
{
  (*this)->setVisible(true);
  use = true;
  this->setTimeOut(3);
  this->setPos(pos);
}

void			ABomb::setPower(int power)
{
  if (_power > 5)
    return ;
  _power = power;
}

int			ABomb::getPower() const
{
  return (_power);
}
