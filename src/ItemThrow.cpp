//
// ItemThrow.cpp for ITEM THROW in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Mon May  9 17:42:59 2016 Victor Gouet
// Last update Mon May  9 21:31:50 2016 Victor Gouet
//

#include "../include/ItemThrow.hpp"

ItemThrow::ItemThrow(irr::core::vector2df const &pos)
  : AItem(pos, "media/bulbizarre.md2", "media/bulbizarre.png", ITEM)
{

}

ItemThrow::~ItemThrow()
{

}

#include <iostream>

void		ItemThrow::use()
{
  std::cout << "USE ITEM THROW" << std::endl;
}
