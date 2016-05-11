//
// ItemThrow.cpp for ITEM THROW in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Mon May  9 17:42:59 2016 Victor Gouet
// Last update Wed May 11 17:59:29 2016 Victor Gouet
//

#include "../include/ItemThrow.hpp"
#include "../include/Texture.hpp"
#include "../include/BomberMap.hpp"

ItemThrow::ItemThrow(irr::core::vector2df const &pos)
  : AItem(pos, BomberManTexture::itemThrowMD,
	  BomberManTexture::itemThrowTexture, ITEM)
{

}

ItemThrow::~ItemThrow()
{

}

#include <iostream>

void		ItemThrow::use(irr::core::vector2df const &playerPos,
			       irr::core::vector2df const &dir)
{
  std::vector<AGameObject*>   objs = BomberMap::getMap()->getObjsFromVector2(playerPos + dir);

  for (std::vector<AGameObject*>::iterator it = objs.begin(); it != objs.end(); ++it) {
    if ((*it)->getType() == AGameObject::BOMB)
      {
	ABomb	*bomb;
	if ((bomb = dynamic_cast<ABomb *>(*it)))
	  {
	    bomb->setVelocity(dir);
	  }
      }
  }
}
