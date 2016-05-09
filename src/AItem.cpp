//
// AItem.cpp for ITEM in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Mon May  9 17:27:09 2016 Victor Gouet
// Last update Mon May  9 17:35:56 2016 Victor Gouet
//

#include "../include/AItem.hpp"

AItem::AItem(irr::core::vector2df const &pos, std::string const &mesh,
	     std::string const &texture, AGameObject::Type type)
  : AGameObject(pos, mesh, texture, type)
{

}

AItem::~AItem()
{

}
