//
// ItemThrow.cpp for ITEM THROW in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Mon May  9 17:42:59 2016 Victor Gouet
// Last update Tue May 10 15:08:53 2016 Victor Gouet
//

#include "../include/ItemThrow.hpp"
#include "../include/Texture.hpp"

ItemThrow::ItemThrow(irr::core::vector2df const &pos)
  : AItem(pos, BomberManTexture::itemThrowMD,
	  BomberManTexture::itemThrowTexture, ITEM)
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
