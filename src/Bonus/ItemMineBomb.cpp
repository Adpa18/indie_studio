//
// ItemMineBomb.cpp for MINE in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Sun May 22 12:58:37 2016 Victor Gouet
// Last update Mon May 23 19:09:26 2016 Victor Gouet
//

#include "../include/ItemMineBomb.hpp"
#include "../include/Texture.hpp"
#include "../include/BomberMap.hpp"

ItemMineBomb::ItemMineBomb(irr::core::vector2df const &pos)
  : AItem(pos, BomberManTexture::getModel("itemMineBomb").mesh,
	  BomberManTexture::getModel("itemMineBomb").texture, "ItemMineBomb", ITEM)
{
}

ItemMineBomb::~ItemMineBomb()
{

}

#include <iostream>

void		ItemMineBomb::use(irr::core::vector2df const &playerPos,
			       irr::core::vector2df const &dir)
{
  std::vector<AGameObject *>	objs = BomberMap::getMap()->getObjsFromVector2(playerPos + dir);
  
  for (std::vector<AGameObject *>::iterator it = objs.begin(), end = objs.end() ; it != end ; ++it)
    {
      if ((*it)->getType() == AGameObject::NONE || (*it)->getType() == AGameObject::BOMB)
	return ;
    }
  MineBomb      *mine = new MineBomb();

  *mine << (playerPos + dir);
}
