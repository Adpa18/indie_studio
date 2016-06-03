//
// BonusBombUp.cpp for BONUS UP in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Mon May  9 15:54:55 2016 Victor Gouet
// Last update Mon May 23 18:35:12 2016 Victor Gouet
//

#include "../include/BonusFireBomb.hpp"
#include "../include/FragBomb.hpp"
#include "../include/BombFactory.hpp"
#include "../include/Texture.hpp"
#include "SoundManager.hpp"

BonusFireBomb::BonusFireBomb(irr::core::vector2df const &pos)
  : ABonus(pos, BomberManTexture::getModel("bonusFireBomb").mesh,
	   BomberManTexture::getModel("bonusFireBomb").texture, "BonusFireBomb", BONUS)
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
  BombFactory::AddBomb<FireBomb>(*(player.getBombContainer()), player->getID());
  SoundManager::getManager()->play("BonusFireBomb.wav", (*this)->getID(), false, 0.8);
}

void	        BonusFireBomb::dead()
{
  (*this)->setVisible(false);
}

bool	        BonusFireBomb::isDestructible() const
{
  return (true);
}
