//
// Bomb.cpp for BOMB in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Thu Apr 28 16:25:11 2016 Victor Gouet
// Last update Fri Apr 29 11:41:39 2016 Victor Gouet
//

#include "../include/Bomb.hpp"
#include <iostream>
#include <unistd.h>

Bomb::Bomb() : AGameObject(irr::core::vector3df(0, 0, 0), "media/caisse")
{
  alive = true;
  use = false;
  (*this)->setVisible(false);
  threadBomb = new std::thread([&] {run(); });
  _power = 3;
}

Bomb::Bomb(Bomb const &other) : AGameObject(irr::core::vector3df(0, 0, 0), "media/caisse")
{
  *this = other;
}

Bomb	&Bomb::operator=(Bomb const &other)
{
  alive = true;
  use = false;
  (*this)->setVisible(false);
  threadBomb = new std::thread([&] {run(); });
  this->_power = other._power;
  return (*this);
}

Bomb::~Bomb()
{
  alive = false;
  use = true;
  condVar.notify_one();
  threadBomb->join();
  delete threadBomb;
}

void			Bomb::onExplosion()
{
  if (!alive)
    return ;
  (*this)->setVisible(false);
  use = false;
}

void				Bomb::run()
{
  while (alive)
    {
      std::unique_lock<std::mutex>	lk(_mutex);

      while (!use)
	condVar.wait(lk);
      if (alive == false)
	{
	  lk.unlock();
	  return ;
	}
      (*this)->setVisible(true);
      sleep(3);
      onExplosion();      
    }
}


bool			Bomb::isAlive() const
{
  return (alive);
}

bool			Bomb::isUse() const
{
  return (use);
}

void			Bomb::operator<<(irr::core::vector3df const &pos)
{
  std::lock_guard<std::mutex> lock(_mutex);
  use = true;
  (*this)->setPosition(pos);
  condVar.notify_one();
}
