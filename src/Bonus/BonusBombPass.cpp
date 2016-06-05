//
// BonusBombPass.cpp for BOMB PASS in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Thu May 12 12:15:24 2016 Victor Gouet
// Last update Sun Jun  5 16:48:50 2016 Matthieu Tavernier
//

#include "BonusBombPass.hpp"
#include "Texture.hpp"
#include "SoundManager.hpp"

BonusBombPass::BonusBombPass(irr::core::vector2df const &pos)
  : ABonus(pos, BomberManTexture::getModel("bonusBombPass").mesh,
	   BomberManTexture::getModel("bonusBombPass").texture, "BonusBombPass", BONUS)
{

}

BonusBombPass::~BonusBombPass()
{
  dead();
}

#include <iostream>

void	        BonusBombPass::take(ACharacter &player)
{
  std::cout << "Bonus BOMB PASS ADD" << std::endl;
  player.setBombPass(true);
  SoundManager::getManager()->play("BonusBombPass.wav", (*this)->getID(), false, 0.8);
}

void	        BonusBombPass::dead()
{
  (*this)->setVisible(false);
  this->setPos(irr::core::vector2df(1000, 1000));
}
