//
// BonusInvincible.cpp for INVICIBLE in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Thu May 12 18:24:43 2016 Victor Gouet
// Last update Wed Jun  1 13:58:26 2016 Victor Gouet
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
  // player.setBombPass(true);
  // player.setLifeUp();
  // player.setMoveSpeed(ACharacter::BASICSPEED / 2);
  // player->setScale(irr::core::vector3df(2.5, 2.5, 2.5));
  // BombFactory::AddBomb<FireBomb>(*(player.getBombContainer()));
   SoundManager::getManager()->stop(player.getID());
  SoundManager::getManager()->play("BonusInvincible.wav", player.getID(), false, 0.8);
}

void	        BonusInvincible::dead()
{
  (*this)->setVisible(false);
}

bool	        BonusInvincible::isDestructible() const
{
  return (true);
}
