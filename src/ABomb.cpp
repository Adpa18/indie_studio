//
// Bomb.cpp for BOMB in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Thu Apr 28 16:25:11 2016 Victor Gouet
// Last update Wed May 11 18:22:24 2016 Victor Gouet
//

#include <iostream>
#include <unistd.h>
#include "../include/ABomb.hpp"
#include "../include/BombFactory.hpp"
#include "../include/BomberMap.hpp"

ABomb::ABomb(std::string const &mesh, std::string const &texture) :
  AGameObject(irr::core::vector2df(-1000, -1000),
	      mesh, texture, AGameObject::BOMB),
  mesh(mesh), texture(texture)
{
  _arrived = true;
  then = IrrlichtController::getDevice()->getTimer()->getTime();
  dir = irr::core::vector2df(0, 0);
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
  _arrived = true;
  then = IrrlichtController::getDevice()->getTimer()->getTime();
  dir = irr::core::vector2df(0, 0);
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

void			ABomb::setVelocity(irr::core::vector2df const &_dir)
{
  dir = _dir;
  _arrived = false;
}

void			ABomb::updateTimeOut()
{
  float   distance = this->getRealPos().getDistanceFrom(this->getMapPos() + dir);
  const irr::u32 now = IrrlichtController::getDevice()->getTimer()->getTime();
  this->frameDeltaTime = (irr::f32)(now - this->then) / 1000.f;

  if (!_arrived)
    {
      std::vector<AGameObject*>   objs = BomberMap::getMap()->getObjsFromVector2(this->getMapPos() + dir);
      if (objs.size() > 0)
	{
	  _arrived = true;
	}
      if (use && !_arrived)
	{
	  if (distance < 0.2)
	    {
	      std::vector<AGameObject*>   objs = BomberMap::getMap()->getObjsFromVector2(this->getMapPos() + dir + dir);
	      if (objs.size() > 0)
		_arrived = true;
	      this->setPos(this->getMapPos() + dir);
	      return;
	    }
	  (*this)->setPosition(irr::core::vector3df((*this)->getPosition().X + dir.X * frameDeltaTime * 300, 0, (*this)->getPosition().Z + dir.Y * frameDeltaTime * 300));
	}
    }
  then = now;
}

void                        ABomb::dead()
{
  
  if (use)
    {
      _arrived = true;
      use = false;
      willExplose();
      disable();
    }
}

bool			ABomb::isDestructible() const
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
  then = IrrlichtController::getDevice()->getTimer()->getTime();
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
