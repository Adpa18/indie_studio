//
// BonusAtomicBomb.cpp for BOMB in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Sat May 21 12:19:25 2016 Victor Gouet
// Last update Sat May 21 12:27:29 2016 Victor Gouet
//

#include "../include/BonusAtomicBomb.hpp"
#include "../include/BombFactory.hpp"
#include "../include/Texture.hpp"
#include "../include/AtomicBomb.hpp"

BonusAtomicBomb::BonusAtomicBomb(irr::core::vector2df const &pos)
  : ABonus(pos, BomberManTexture::getModel("bonusAtomicBomb").mesh,
    BomberManTexture::getModel("bonusAtomicBomb").texture, BONUS)
{

}

BonusAtomicBomb::~BonusAtomicBomb()
{
  dead();
}

#include <iostream>

void	        BonusAtomicBomb::take(ACharacter &player)
{
  std::cout << "Bonus ATOMIC BOMB ADD" << std::endl;
  BombFactory::AddBomb<AtomicBomb>(*(player.getBombContainer()), player->getID());
}

void	        BonusAtomicBomb::dead()
{
  (*this)->setVisible(false);
}

bool	        BonusAtomicBomb::isDestructible() const
{
  return (true);
}
