//
// BonusSpeed.cpp for BONUS SPEED in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Mon May  9 13:37:03 2016 Victor Gouet
// Last update Tue May 10 15:08:02 2016 Victor Gouet
//

#include "../include/BonusSpeed.hpp"
#include "../include/Texture.hpp"

BonusSpeed::BonusSpeed(irr::core::vector2df const &pos)
  : ABonus(pos, BomberManTexture::bonusSpeedMD,
	   BomberManTexture::bonusSpeedTexture, BONUS)
{

}

BonusSpeed::~BonusSpeed()
{
  dead();
}

#include <iostream>

void		BonusSpeed::take(ACharacter &player)
{
  std::cout << "BONUS SPEED TAKEN !" << std::endl;
  player.setMoveSpeed(player.getMoveSpeed() + 0.5);
}

void		BonusSpeed::dead()
{
  (*this)->setVisible(false);
}

bool		BonusSpeed::isDestructible() const
{
  return (true);
}
