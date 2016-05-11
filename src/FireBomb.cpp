//
// FireBomb.cpp for FIRE in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Fri Apr 29 13:38:52 2016 Victor Gouet
// Last update Wed May 11 16:34:22 2016 Victor Gouet
//

#include "../include/FireBomb.hpp"
#include "../include/BomberMap.hpp"
#include "../include/Particule.hpp"
#include "../include/Texture.hpp"
#include "../include/Explosion.hpp"

FireBomb::FireBomb()
  : ABomb(BomberManTexture::fireBombMD, BomberManTexture::fireBombTexture)
{

}

FireBomb::~FireBomb()
{

}

FireBomb	&FireBomb::operator=(ABomb const *other)
{
  use = false;
  (*this)->setVisible(false);
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

//    std::vector<AGameObject *>   objs;
//    AGameObject::Type           type;
//
//    for (std::vector<AGameObject*>::iterator it = objs.begin(); it != objs.end(); ++it) {
//        new Explosion(pos, 3);
//        if (this != (*it)) {
//            AGameObject *obj = (*it);
//	    obj->dead();
//	    if (obj->isDestructible())
//	      delete obj;
//        }
//    }
//    for (int power = 1; power <= this->_power; ++power) {
//        objs = BomberMap::getMap()->getObjsFromVector2(pos + irr::core::vector2df(-power, 0));
//        for (std::vector<AGameObject*>::iterator it = objs.begin(); it != objs.end(); ++it) {
//            type = (*it)->getType();
//            if (type != AGameObject::BLOCK) {
//	      AGameObject *obj = (*it);
//	      obj->dead();
//	      if (obj->isDestructible())
//		delete obj;
//            }
//            if (type == AGameObject::BLOCK || type == AGameObject::OTHER) {
//                break;
//            }
//        }
//        new Explosion(pos + irr::core::vector2df(-power, 0), 3);
//    }
//    for (int power = 1; power <= this->_power; ++power) {
//        objs = BomberMap::getMap()->getObjsFromVector2(pos + irr::core::vector2df(power, 0));
//        for (std::vector<AGameObject*>::iterator it = objs.begin(); it != objs.end(); ++it) {
//            type = (*it)->getType();
//            if (type != AGameObject::BLOCK) {
//                AGameObject *obj = (*it);
//		obj->dead();
//		if (obj->isDestructible())
//		  delete obj;
//            }
//            if (type == AGameObject::BLOCK || type == AGameObject::OTHER) {
//                break;
//            }
//        }
//        new Explosion(pos + irr::core::vector2df(power, 0), 3);
//    }
//    for (int power = 1; power <= this->_power; ++power) {
//        objs = BomberMap::getMap()->getObjsFromVector2(pos + irr::core::vector2df(0, -power));
//        for (std::vector<AGameObject*>::iterator it = objs.begin(); it != objs.end(); ++it) {
//            type = (*it)->getType();
//            if (type != AGameObject::BLOCK) {
//                AGameObject *obj = (*it);
//		obj->dead();
//		if (obj->isDestructible())
//		  delete obj;
//            }
//            if (type == AGameObject::BLOCK || type == AGameObject::OTHER) {
//                break;
//            }
//        }
//        new Explosion(pos + irr::core::vector2df(0, -power), 3);
//    }
//    for (int power = 1; power <= this->_power; ++power) {
//        objs = BomberMap::getMap()->getObjsFromVector2(pos + irr::core::vector2df(0, power));
//        for (std::vector<AGameObject*>::iterator it = objs.begin(); it != objs.end(); ++it) {
//            type = (*it)->getType();
//            if (type != AGameObject::BLOCK) {
//                AGameObject *obj = (*it);
//		obj->dead();
//		if (obj->isDestructible())
//		  delete obj;
//            }
//            if (type == AGameObject::BLOCK || type == AGameObject::OTHER) {
//                break;
//            }
//        }
//        new Explosion(pos + irr::core::vector2df(0, power), 3);
//    }
}

bool    FireBomb::killObjects(irr::core::vector2df const &pos)
{
    std::vector<AGameObject *>   objs;
    AGameObject::Type           type;
    bool                        stop = false;

    objs = BomberMap::getMap()->getObjsFromVector2(pos);
    for (std::vector<AGameObject*>::iterator it = objs.begin(); it != objs.end(); ++it) {
        if (this == (*it)) {
            continue;
        }
        type = (*it)->getType();
        if (type != AGameObject::BLOCK) {
            AGameObject *obj = (*it);
            obj->dead();
            if (type != AGameObject::BOOM && obj->isDestructible()) {
                delete obj;
            }
        }
        if (type == AGameObject::BLOCK || type == AGameObject::OTHER) {
            stop = true;
        }
    }
    if (!stop) {
        new Explosion(pos, 1);
    }
    return (stop);
}