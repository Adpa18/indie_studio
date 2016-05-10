//
// Bomb.cpp for BOMB in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Thu Apr 28 16:25:11 2016 Victor Gouet
// Last update Tue May 10 15:03:01 2016 Victor Gouet
//

#include <iostream>
#include <unistd.h>
#include "../include/ABomb.hpp"

ABomb::ABomb(std::string const &mesh, std::string const &texture) :
  AGameObject(irr::core::vector2df(0, 0), mesh, texture, AGameObject::BOMB),
  mesh(mesh), texture(texture)								    
{
  alive = true;
  use = false;
  (*this)->setVisible(false);
  threadBomb = new std::thread([&] {this->run(); });
  _power = 3;
  __active = false;
}

ABomb::ABomb(ABomb const *other) : AGameObject(irr::core::vector2df(0, 0),
					       other->mesh, other->texture)
{
  *this = other;
}

ABomb	&ABomb::operator=(ABomb const *other)
{
  alive = true;
  use = false;
  (*this)->setVisible(false);
  threadBomb = new std::thread([&] {run(); });
  this->_power = other->_power;
  this->__active = false;
  this->mesh = other->mesh;
  this->texture = other->texture;
  return (*this);
}

ABomb::~ABomb()
{
  _mutex.lock();
  alive = false;
  use = true;
  // condVar.notify_one();
  threadBomb->join();
  _mutex.unlock();
  delete threadBomb;
}

void                        ABomb::dead()
{
  __active = true;
  use = false;
}

bool				ABomb::isDestructible() const
{
  return (false);
}

void				ABomb::run()
{
  while (alive)
    {
      int i = 0;

      while (!isNotUse() && isAlive())
	usleep(0);
      _mutex.lock();
      if (alive == false)
	{
	  _mutex.unlock();
	  return ;
	}
      while (i < 3000 && __active == false)
	{
	  usleep(1000);
	  ++i;
	}
      // sleep(3);
      if (!alive)
	{
	  _mutex.unlock();
	  return ;
	}
      __active = true;
      use = false;
      _mutex.unlock();
    }
}

bool			ABomb::isActive() const
{
  bool			_active;

  _active = false;
  if (_mutex.try_lock())
    {
      _active = __active;
      if (__active == true)
	__active = false;
      _mutex.unlock();
    }
  return (_active);
}

bool			ABomb::isAlive() const
{
  bool			_alive;

  _alive = true;
  if (_mutex.try_lock())
    {
      _alive = alive;
      _mutex.unlock();
    }
  return (_alive);
}


bool			ABomb::isNotUse() const
{
  bool			_use;

  _use = false;
  if (_mutex.try_lock())
    {
      _use = use;
      _mutex.unlock();
    }
  return (_use);
  // return (use);
}

bool			ABomb::isUse() const
{
  bool			_use;

  _use = true;
  if (_mutex.try_lock())
    {
      _use = use;
      _mutex.unlock();
    }
  return (_use);
}

void		ABomb::disable()
{
  this->setPos(irr::core::vector2df(-1000, -1000));
}

void			ABomb::operator<<(irr::core::vector2df const &pos)
{
  _mutex.lock();
  (*this)->setVisible(true);
  use = true;
    this->setPos(pos);
  _mutex.unlock();
}

void			ABomb::setPower(int power)
{
  if (_power > 7)
    return ;
  _power = power;
}

int			ABomb::getPower() const
{
  return (_power);
}
