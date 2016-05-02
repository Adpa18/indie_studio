//
// Bomb.cpp for BOMB in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Thu Apr 28 16:25:11 2016 Victor Gouet
// Last update Sat Apr 30 10:04:36 2016 Victor Gouet
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
  return (*this);
}

ABomb::~ABomb()
{
  _mutex.lock();
  alive = false;
  use = true;
  condVar.notify_one();
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
      std::unique_lock<std::mutex>	lk(_mutex);

      while (!use && alive)
	condVar.wait(lk);
      if (alive == false)
	{
	  lk.unlock();
	  return ;
	}
      (*this)->setVisible(true);
      sleep(3);
      if (!alive)
	return ;
      willExplose();
      use = false;
    }
}


bool			ABomb::isAlive() const
{
  return (alive);
}

bool			ABomb::isUse() const
{
  return (use);
}

void			ABomb::operator<<(irr::core::vector3df const &pos)
{
  std::lock_guard<std::mutex> lock(_mutex);
  use = true;
  (*this)->setPosition(pos);
  condVar.notify_one();
}

int			ABomb::getPower() const
{
  return (_power);
}
