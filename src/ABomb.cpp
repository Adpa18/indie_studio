//
// Bomb.cpp for BOMB in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Thu Apr 28 16:25:11 2016 Victor Gouet
// Last update Thu May  5 15:53:20 2016 Victor Gouet
//

#include "../include/ABomb.hpp"
#include <iostream>
#include <unistd.h>

ABomb::ABomb() : AGameObject(irr::core::vector3df(0, 0, 0), "media/pokeball.md2", "media/pokeball.png")
{
  alive = true;
  use = false;
  (*this)->setVisible(false);
  threadBomb = new std::thread([&] {this->run(); });
  _power = 3;
  __active = false;
}

ABomb::ABomb(ABomb const *other) : AGameObject(irr::core::vector3df(0, 0, 0),
					       "media/pokeball.md2", "media/pokeball.png")
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

// void			ABomb::willExplose()
// {
//   (*this)->setVisible(false);
// }

void				ABomb::run()
{
  while (alive)
    {
      // std::unique_lock<std::mutex>	lk(_mutex);

      while (!isUse() && isAlive())
	usleep(0);
      _mutex.lock();
	//condVar.wait(lk);
      if (alive == false)
	{
	  _mutex.unlock();
	  // lk.unlock();
	  return ;
	}
      //(*this)->setVisible(true);
      //_mutex.unlock();
      sleep(3);
      //_mutex.lock();
      if (!alive)
	{
	  _mutex.unlock();
	  return ;
	}
      __active = true;
      // willExplose();
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
  // return (use);
}

void			ABomb::operator<<(irr::core::vector3df const &pos)
{
  // std::lock_guard<std::mutex> lock(_mutex);
  _mutex.lock();
  (*this)->setVisible(true);
  use = true;
  (*this)->setPosition(pos);
  _mutex.unlock();
  // condVar.notify_one();
}

int			ABomb::getPower() const
{
  return (_power);
}
