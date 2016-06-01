//
// FireBomb.cpp for FIRE in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Fri Apr 29 13:38:52 2016 Victor Gouet
// Last update Wed Jun  1 15:17:54 2016 Victor Gouet
//

#include "../include/FireBomb.hpp"
#include "../include/BomberMap.hpp"
#include "../include/Texture.hpp"
#include "../include/Explosion.hpp"

FireBomb::FireBomb(int id)
  : ABomb(BomberManTexture::getModel("fireBomb").mesh,
	  BomberManTexture::getModel("fireBomb").texture, 3, id)
{

}

FireBomb::~FireBomb()
{

}

FireBomb	&FireBomb::operator=(ABomb const *other)
{
  use = false;
  timeout = 3;
  (*this)->setVisible(false);
  this->_power = other->getPower();
  return (*this);
}

FireBomb::FireBomb(ABomb const *other) : ABomb(other)
{
  *this = other;
}

#include <iostream>

void		FireBomb::willExplose()
{
    irr::core::vector2df        pos = this->getMapPos();

    this->killObjects(pos);
    for (int power = 1; power <= this->_power; ++power) {
        if (this->killObjects(pos + irr::core::vector2df(-power, 0))) {
            break;
        }
    }
    for (int power = 1; power <= this->_power; ++power) {
        if (this->killObjects(pos + irr::core::vector2df(power, 0))) {
            break;
        }
    }
    for (int power = 1; power <= this->_power; ++power) {
        if (this->killObjects(pos + irr::core::vector2df(0, -power))) {
            break;
        }
    }
    for (int power = 1; power <= this->_power; ++power) {
        if (this->killObjects(pos + irr::core::vector2df(0, power))) {
            break;
        }
    }
}

bool    FireBomb::killObjects(irr::core::vector2df const &pos)
{
    std::vector<AGameObject *>   objs;
    AGameObject::Type           type;
    bool                        stop = false;

    type = AGameObject::NONE;
    objs = BomberMap::getMap()->getObjsFromVector2(pos);
    for (std::vector<AGameObject*>::iterator it = objs.begin(); it != objs.end(); ++it) {
        if (this == (*it)) {
            continue;
        }
        type = (*it)->getType();
        if (type != AGameObject::BLOCK && type != AGameObject::NONE && type != AGameObject::BOOM) {
            AGameObject *obj = (*it);
            obj->dead();
            if (type != AGameObject::BOOM
		&& !obj->isObjectTimeOut()
		&& obj->isDestructible()) {
	        delete obj;
            }
        }
        if (type == AGameObject::BLOCK || type == AGameObject::OTHER) {
            stop = true;
        }
    }
    // if (!stop) {
        // new Explosion(pos, 1);
    if (type != AGameObject::BLOCK) {
        new Explosion(pos, BomberManTexture::getModel("fire").texture, 0.5);
    }
    // }
    return (stop);
}
