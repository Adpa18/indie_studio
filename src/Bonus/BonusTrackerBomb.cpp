//
// BonusTrackerBomb.cpp for TRACKER in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Sat May 21 12:31:11 2016 Victor Gouet
// Last update Mon May 23 18:36:09 2016 Victor Gouet
//

#include "../include/BonusTrackerBomb.hpp"
#include "../include/TrackerBomb.hpp"
#include "../include/BombFactory.hpp"
#include "../include/Texture.hpp"
#include "SoundManager.hpp"

BonusTrackerBomb::BonusTrackerBomb(irr::core::vector2df const &pos)
  : ABonus(pos, BomberManTexture::getModel("bonusTrackerBomb").mesh,
	   BomberManTexture::getModel("bonusTrackerBomb").texture, "BonusTrackerBomb", BONUS)
{
}

BonusTrackerBomb::~BonusTrackerBomb()
{
  dead();
}

#include <iostream>

void	        BonusTrackerBomb::take(ACharacter &player)
{
  std::cout << "Bonus TRACKER BOMB ADD" << std::endl;
  BombFactory::AddBomb<TrackerBomb>(*(player.getBombContainer()), player->getID());
  SoundManager::getManager()->play("BonusTrackerBomb.wav", (*this)->getID(), false, 0.8);
}

void	        BonusTrackerBomb::dead()
{
  (*this)->setVisible(false);
}

bool	        BonusTrackerBomb::isDestructible() const
{
  return (true);
}
