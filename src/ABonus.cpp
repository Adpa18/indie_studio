//
// ABonus.cpp for BONUS in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Mon May  9 13:25:32 2016 Victor Gouet
// Last update Mon May  9 13:31:13 2016 Victor Gouet
//

#include "../include/ABonus.hpp"

ABonus::ABonus(irr::core::vector2df const &pos, std::string const &mesh,
	       std::string const &texture, Type type)
  : AGameObject(pos, mesh, texture, type)
{
}

ABonus::~ABonus()
{
}
