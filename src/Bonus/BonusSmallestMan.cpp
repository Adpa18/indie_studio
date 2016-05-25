//
// BonusSmallestMan.cpp for SMALLEST in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Thu May 12 14:33:06 2016 Victor Gouet
// Last update Mon May 23 18:35:48 2016 Victor Gouet
//

#include "../include/BonusSmallestMan.hpp"
#include "../include/Texture.hpp"

BonusSmallestMan::BonusSmallestMan(irr::core::vector2df const &pos)
  : ABonus(pos, BomberManTexture::getModel("bonusSmallestMan").mesh,
	   BomberManTexture::getModel("bonusSmallestMan").texture, "BonusSmallestMan", BONUS)
{

}

BonusSmallestMan::~BonusSmallestMan()
{
  dead();
}

#include <iostream>

void	        BonusSmallestMan::take(ACharacter &player)
{
  std::cout << "Bonus BonusSmallestMan ADD" << std::endl;

  player.setMoveSpeed(ACharacter::BASICSPEED * 2);
  player->setScale(irr::core::vector3df(0.5, 0.5, 0.5));
}

void	        BonusSmallestMan::dead()
{
  (*this)->setVisible(false);
}

bool	        BonusSmallestMan::isDestructible() const
{
  return (true);
}
