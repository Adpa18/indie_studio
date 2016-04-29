//
// FireBomb.cpp for FIRE in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Fri Apr 29 13:38:52 2016 Victor Gouet
// Last update Fri Apr 29 16:51:45 2016 Victor Gouet
//

#include "../include/FireBomb.hpp"
#include <iostream>

FireBomb::~FireBomb()
{

}

FireBomb::FireBomb() : ABomb()
{

}

FireBomb	&FireBomb::operator=(ABomb const *other)
{
  alive = true;
  use = false;
  (*this)->setVisible(false);
  newThreadBomb();
  this->_power = other->getPower();
  return (*this);
}

FireBomb::FireBomb(ABomb const *other)
{
  *this = other;
}

void		FireBomb::willExplose()
{
  (*this)->setVisible(false);
  std::cout << "EXPLOSE DANS FIREBOMB" << std::endl;
}
