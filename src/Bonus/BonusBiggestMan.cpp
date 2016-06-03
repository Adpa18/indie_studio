//
// BonusBiggestMan.cpp for BIGGEST in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Thu May 12 12:55:40 2016 Victor Gouet
// Last update Mon May 23 18:34:51 2016 Victor Gouet
//

#include "../include/BonusBiggestMan.hpp"
#include "../include/Texture.hpp"
#include "SoundManager.hpp"

BonusBiggestMan::BonusBiggestMan(irr::core::vector2df const &pos)
  : ABonus(pos, BomberManTexture::getModel("bonusBiggestMan").mesh,
	   BomberManTexture::getModel("bonusBiggestMan").texture, "BonusBiggestMan", BONUS)
{

}

BonusBiggestMan::~BonusBiggestMan()
{
  dead();
}

#include <iostream>

void	        BonusBiggestMan::take(ACharacter &player)
{
  std::cout << "Bonus BonusBiggestMan ADD" << std::endl;
  // player.setBombPass(true);
  player.setLifeUp();
  player.setMoveSpeed(ACharacter::BASICSPEED / 2);
  player->setScale(irr::core::vector3df(2.5, 2.5, 2.5));
  // BombFactory::AddBomb<FireBomb>(*(player.getBombContainer()));
  SoundManager::getManager()->play("BonusBiggestMan.wav", (*this)->getID(), false, 0.8);
}

void	        BonusBiggestMan::dead()
{
  (*this)->setVisible(false);
}

bool	        BonusBiggestMan::isDestructible() const
{
  return (true);
}
