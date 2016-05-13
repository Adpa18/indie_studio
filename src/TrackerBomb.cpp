//
// TrackerBomb.cpp for TRACKER BOMB in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Fri May 13 11:04:11 2016 Victor Gouet
// Last update Fri May 13 11:20:48 2016 Victor Gouet
//

#include "../include/TrackerBomb.hpp"
#include "../include/BomberMap.hpp"
#include "../include/Texture.hpp"
#include "../include/Explosion.hpp"

TrackerBomb::TrackerBomb()
  : ABomb(BomberManTexture::getModel("trackerBomb").mesh,
	  BomberManTexture::getModel("trackerBomb").texture, 5)
{

}

TrackerBomb::~TrackerBomb()
{

}

TrackerBomb	&TrackerBomb::operator=(ABomb const *other)
{
  use = false;
  (*this)->setVisible(false);
  this->_power = other->getPower();
  return (*this);
}

TrackerBomb::TrackerBomb(ABomb const *other) : ABomb(other)
{
  *this = other;
}

#include <iostream>

void	TrackerBomb::updateTimeOut()
{
  std::cout << "UPDATE TRACKER BOMB" << std::endl;
}

void		TrackerBomb::willExplose()
{
  std::cout << "BOOM" << std::endl;
}
