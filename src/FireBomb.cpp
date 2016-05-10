//
// FireBomb.cpp for FIRE in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Fri Apr 29 13:38:52 2016 Victor Gouet
// Last update Tue May 10 22:33:11 2016 Victor Gouet
//

#include "../include/FireBomb.hpp"
#include "../include/BomberMap.hpp"
#include "../include/Particule.hpp"
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
    int power;
    stop = false;
    for (power = 1; power <= this->_power; ++power) {
        if (stop) {
            break;
        }
        objs = BomberMap::getMap()->getObjsFromVector2(pos + irr::core::vector2df(-power, 0));
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
    Particule p1((*this)->getPosition(), irr::core::vector3df(-1, 0, 0), power);
    stop = false;
    for (power = 1; power <= this->_power; ++power) {
        if (stop)
            break;
        objs = BomberMap::getMap()->getObjsFromVector2(pos + irr::core::vector2df(power, 0));
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
    Particule p2((*this)->getPosition(), irr::core::vector3df(1, 0, 0), power);
    stop = false;
    for (power = 1; power <= this->_power; ++power) {
        if (stop)
            break;
        objs = BomberMap::getMap()->getObjsFromVector2(pos + irr::core::vector2df(0, -power));
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
    Particule p3((*this)->getPosition(), irr::core::vector3df(1, 0, -1), power);
    stop = false;
    for (power = 1; power <= this->_power; ++power) {
        if (stop)
            break;
        objs = BomberMap::getMap()->getObjsFromVector2(pos + irr::core::vector2df(0, power));
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
    Particule p4((*this)->getPosition(), irr::core::vector3df(0, 0, 1), power);
    disable();
}
