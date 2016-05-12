//
// BonusPower.cpp for BONUS in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Mon May  9 15:05:25 2016 Victor Gouet
// Last update Tue May 10 15:06:13 2016 Victor Gouet
//

#include "../include/BonusPower.hpp"
#include "../include/Texture.hpp"

BonusPower::BonusPower(irr::core::vector2df const &pos)
  : ABonus(pos, BomberManTexture::getModel("bonusPower").mesh,
	   BomberManTexture::getModel("bonusPower").texture, BONUS)
{

}

BonusPower::~BonusPower()
{
  dead();
}

#include <iostream>

void		BonusPower::take(ACharacter &player)
{
  std::cout << "Bonus POWER UP" << std::endl;
  // player.setMoveSpeed(player.getMoveSpeed() + 0.5);
  player.increasePowerBomb();
}

void	        BonusPower::dead()
{
  (*this)->setVisible(false);
}

bool	        BonusPower::isDestructible() const
{
  return (true);
}
