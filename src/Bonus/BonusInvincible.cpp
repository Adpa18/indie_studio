//
// BonusInvincible.cpp for INVICIBLE in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Thu May 12 18:24:43 2016 Victor Gouet
// Last update Sun Jun  5 12:29:24 2016 Matthieu Tavernier
//

#include "../../include/BonusInvincible.hpp"
#include "../../include/Texture.hpp"
#include "../../include/SoundManager.hpp"

BonusInvincible::BonusInvincible(irr::core::vector2df const &pos)
        : ABonus(pos, BomberManTexture::getModel("bonusInvincible").mesh,
                 BomberManTexture::getModel("bonusInvincible").texture, "BonusInvincible", BONUS)
{

}

BonusInvincible::~BonusInvincible()
{
  dead();
}

#include <iostream>

void	        BonusInvincible::take(ACharacter &player)
{
  std::cout << "Bonus BonusInvincible ADD" << std::endl;
  player.invincibleEnabledDuringPeriod(5000000);
  SoundManager::getManager()->stop(player.getID());
  SoundManager::getManager()->play("BonusInvincible.wav", player.getID(), false, 0.8);
}

void	        BonusInvincible::dead()
{
  (*this)->setVisible(false);
  this->setPos(irr::core::vector2df(1000, 1000));
}
