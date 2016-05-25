//
// BonusFragBomb.cpp for BONUS in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Sat May 21 12:04:39 2016 Victor Gouet
// Last update Mon May 23 18:35:21 2016 Victor Gouet
//

#include "../include/BonusFragBomb.hpp"
#include "../include/FragBomb.hpp"
#include "../include/BombFactory.hpp"
#include "../include/Texture.hpp"

BonusFragBomb::BonusFragBomb(irr::core::vector2df const &pos)
  : ABonus(pos, BomberManTexture::getModel("bonusFragBomb").mesh,
	   BomberManTexture::getModel("bonusFragBomb").texture, "BonusFragBomb", BONUS)
{

}

BonusFragBomb::~BonusFragBomb()
{
  dead();
}

#include <iostream>

void	        BonusFragBomb::take(ACharacter &player)
{
  std::cout << "Bonus FRAG BOMB ADD" << std::endl;
  BombFactory::AddBomb<FragBomb>(*(player.getBombContainer()), player->getID());
}

void	        BonusFragBomb::dead()
{
  (*this)->setVisible(false);
}

bool	        BonusFragBomb::isDestructible() const
{
  return (true);
}
