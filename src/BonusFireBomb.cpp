//
// BonusBombUp.cpp for BONUS UP in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Mon May  9 15:54:55 2016 Victor Gouet
// Last update Tue May 10 15:05:05 2016 Victor Gouet
//

#include "../include/BonusFireBomb.hpp"
#include "../include/BombFactory.hpp"
#include "../include/Texture.hpp"

BonusFireBomb::BonusFireBomb(irr::core::vector2df const &pos)
  : ABonus(pos, BomberManTexture::bonusFireBombMD,
	   BomberManTexture::bonusFireBombTexture, BONUS)
{

}

BonusFireBomb::~BonusFireBomb()
{
  dead();
}

#include <iostream>

void	        BonusFireBomb::take(ACharacter &player)
{
  std::cout << "Bonus FIRE BOMB ADD" << std::endl;
  BombFactory::AddBomb<FireBomb>(*(player.getBombContainer()));
}

void	        BonusFireBomb::dead()
{
  (*this)->setVisible(false);
}

bool	        BonusFireBomb::isDestructible() const
{
  return (true);
}
