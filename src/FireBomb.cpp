//
// FireBomb.cpp for FIRE in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Fri Apr 29 13:38:52 2016 Victor Gouet
// Last update Tue May 10 15:00:41 2016 Victor Gouet
//

#include "../include/FireBomb.hpp"
#include "../include/BomberMap.hpp"
#include "../include/Texture.hpp"

FireBomb::FireBomb() : ABomb(BomberManTexture::fireBombMD,
			     BomberManTexture::fireBombTexture)
{

}

FireBomb::~FireBomb()
{

}

FireBomb	&FireBomb::operator=(ABomb const *other)
{
  alive = true;
  use = false;
  (*this)->setVisible(false);
  newThreadBomb();
  this->_power = other->getPower();
  return (*this);
}

FireBomb::FireBomb(ABomb const *other) : ABomb(other)
{
  *this = other;
}

void		FireBomb::willExplose()
{
    irr::core::vector2df        pos = this->getMapPos();
    std::vector<AGameObject *>   objs;
    AGameObject::Type           type;
    bool                        stop;

    for (std::vector<AGameObject*>::iterator it = objs.begin(); it != objs.end(); ++it) {
        if (this != (*it)) {
            AGameObject *obj = (*it);
	    obj->dead();
	    if (obj->isDestructible())
	      delete obj;
        }
    }
    stop = false;
    for (int i = 1; i <= this->_power; ++i) {
        if (stop)
            break;
        objs = BomberMap::getMap()->getObjsFromVector2(pos + irr::core::vector2df(-i, 0));
        for (std::vector<AGameObject*>::iterator it = objs.begin(); it != objs.end(); ++it) {
            type = (*it)->getType();
            if (type != AGameObject::BLOCK) {
	      AGameObject *obj = (*it);
	      obj->dead();
	      if (obj->isDestructible())
		delete obj;
            }
            if (type == AGameObject::BLOCK || type == AGameObject::OTHER) {
                stop = true;
            }
        }
    }
    stop = false;
    for (int i = 1; i <= this->_power; ++i) {
        if (stop)
            break;
        objs = BomberMap::getMap()->getObjsFromVector2(pos + irr::core::vector2df(i, 0));
        for (std::vector<AGameObject*>::iterator it = objs.begin(); it != objs.end(); ++it) {
            type = (*it)->getType();
            if (type != AGameObject::BLOCK) {
                AGameObject *obj = (*it);
		obj->dead();
		if (obj->isDestructible())
		  delete obj;
            }
            if (type == AGameObject::BLOCK || type == AGameObject::OTHER) {
                stop = true;
            }
        }
    }
    stop = false;
    for (int i = 1; i <= this->_power; ++i) {
        if (stop)
            break;
        objs = BomberMap::getMap()->getObjsFromVector2(pos + irr::core::vector2df(0, -i));
        for (std::vector<AGameObject*>::iterator it = objs.begin(); it != objs.end(); ++it) {
            type = (*it)->getType();
            if (type != AGameObject::BLOCK) {
                AGameObject *obj = (*it);
		obj->dead();
		if (obj->isDestructible())
		  delete obj;
            }
            if (type == AGameObject::BLOCK || type == AGameObject::OTHER) {
                stop = true;
            }
        }
    }
    stop = false;
    for (int i = 1; i <= this->_power; ++i) {
        if (stop)
            break;
        objs = BomberMap::getMap()->getObjsFromVector2(pos + irr::core::vector2df(0, i));
        for (std::vector<AGameObject*>::iterator it = objs.begin(); it != objs.end(); ++it) {
            type = (*it)->getType();
            if (type != AGameObject::BLOCK) {
                AGameObject *obj = (*it);
		obj->dead();
		if (obj->isDestructible())
		  delete obj;
            }
            if (type == AGameObject::BLOCK || type == AGameObject::OTHER) {
                stop = true;
            }
        }
    }
    disable();
}
