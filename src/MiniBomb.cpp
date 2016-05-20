//
// MiniBomb.cpp for MINI in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Fri May 20 16:31:36 2016 Victor Gouet
// Last update Fri May 20 21:05:10 2016 Victor Gouet
//

#include "../include/MiniBomb.hpp"
#include "../include/BomberMap.hpp"
#include "../include/Texture.hpp"
#include "../include/Explosion.hpp"
#include "../include/GameObjectTimeContainer.hpp"

MiniBomb::MiniBomb(int id)
  : ABomb(BomberManTexture::getModel("miniBomb").mesh,
	  BomberManTexture::getModel("miniBomb").texture, 0.5, id)
{
  this->_power = 1;
  use = false;
  timeout = 0.5;
  (*this)->setVisible(false);
}

MiniBomb::~MiniBomb()
{

}

MiniBomb	&MiniBomb::operator=(ABomb const *other)
{
  use = false;
  timeout = 0.5;
  (*this)->setVisible(false);
  this->_power = 1;
  return (*this);
}

MiniBomb::MiniBomb(ABomb const *other) : ABomb(other)
{
  *this = other;
}

#include <iostream>

void		MiniBomb::disable()
{
}

bool		MiniBomb::isDestructible() const
{
  return (true);
}

void		MiniBomb::willExplose()
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

bool    MiniBomb::killObjects(irr::core::vector2df const &pos)
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
        if (type != AGameObject::BLOCK) {
            AGameObject *obj = (*it);
            obj->dead();
            if (type != AGameObject::BOOM && type != AGameObject::BOMB && obj->isDestructible()) {
		delete obj;
            }
        }
        if (type == AGameObject::BLOCK || type == AGameObject::OTHER) {
            stop = true;
        }
    }
    if (type != AGameObject::BLOCK) {
        new Explosion(pos, BomberManTexture::getModel("fire").texture, 1);
    }
    return (stop);
}
