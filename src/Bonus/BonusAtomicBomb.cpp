//
// BonusAtomicBomb.cpp for BOMB in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Sat May 21 12:19:25 2016 Victor Gouet
// Last update Mon May 23 18:34:34 2016 Victor Gouet
//

#include "../include/BonusAtomicBomb.hpp"
#include "../include/BombFactory.hpp"
#include "../include/Texture.hpp"
#include "../include/AtomicBomb.hpp"
#include "SoundManager.hpp"

BonusAtomicBomb::BonusAtomicBomb(irr::core::vector2df const &pos)
  : ABonus(pos, BomberManTexture::getModel("bonusAtomicBomb").mesh,
	   BomberManTexture::getModel("bonusAtomicBomb").texture, "BonusAtomicBomb", BONUS)
{

}

BonusAtomicBomb::~BonusAtomicBomb()
{
  dead();
}

void	        BonusAtomicBomb::take(ACharacter &player)
{
  std::cout << "Bonus ATOMIC BOMB ADD" << std::endl;
  BombFactory::AddBomb<AtomicBomb>(*(player.getBombContainer()), player->getID());
  SoundManager::getManager()->play("takeBonus.wav", (*this)->getID());
}

void	        BonusAtomicBomb::dead()
{
  (*this)->setVisible(false);
}

bool	        BonusAtomicBomb::isDestructible() const
{
  return (true);
}
