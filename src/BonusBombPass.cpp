//
// BonusBombPass.cpp for BOMB PASS in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Thu May 12 12:15:24 2016 Victor Gouet
// Last update Thu May 12 13:18:47 2016 Victor Gouet
//

#include "../include/BonusBombPass.hpp"
#include "../include/Texture.hpp"

BonusBombPass::BonusBombPass(irr::core::vector2df const &pos)
  : ABonus(pos, BomberManTexture::bonusBombPassMD,
	   BomberManTexture::bonusBombPassTexture, BONUS)
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
  // BombFactory::AddBomb<FireBomb>(*(player.getBombContainer()));
}

void	        BonusBombPass::dead()
{
  (*this)->setVisible(false);
}

bool	        BonusBombPass::isDestructible() const
{
  return (true);
}
