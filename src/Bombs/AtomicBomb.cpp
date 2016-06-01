//
// AtomicBomb.cpp for ATOMIC in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Fri May 20 10:51:39 2016 Victor Gouet
// Last update Wed Jun  1 20:34:04 2016 Victor Gouet
//

#include "../include/AtomicBomb.hpp"
#include "../include/BomberMap.hpp"
#include "../include/Texture.hpp"
#include "../include/Explosion.hpp"

AtomicBomb::AtomicBomb(int id)
  : ABomb(BomberManTexture::getModel("atomicBomb").mesh,
	  BomberManTexture::getModel("atomicBomb").texture, 10, id)
{

}

AtomicBomb::~AtomicBomb()
{

}

AtomicBomb	&AtomicBomb::operator=(ABomb const *other)
{
  use = false;
  timeout = 10;
  (*this)->setVisible(false);
  this->_power = other->getPower();
  return (*this);
}

AtomicBomb::AtomicBomb(ABomb const *other) : ABomb(other)
{
  *this = other;
}

void		AtomicBomb::willExplose()
{
    irr::core::vector2df        pos = this->getMapPos();

    this->killObjects(pos);
    // std::cout << _power << std::endl;
    for (int y = -2 ; y <= 2 ; ++y)
      {
	for (int x = -2 ; x <= 2 ; ++x)
	  {
	    irr::core::vector2df	newPos = pos + irr::core::vector2df(x, y);
	    if (newPos.X < 0 || newPos.Y < 0
		|| newPos.X > BomberMap::getMap()->getSize()
		|| newPos.Y > BomberMap::getMap()->getSize())
	      continue;
	    this->killObjects(newPos);
	  }
      }
}

bool    AtomicBomb::killObjects(irr::core::vector2df const &pos)
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
                // delete obj;
	      
                delete obj;
            }
        }
        if (type == AGameObject::BLOCK || type == AGameObject::OTHER) {
            stop = true;
        }
    }
    if (type != AGameObject::BLOCK) {
        new Explosion(pos, BomberManTexture::getModel("fireAtomic").texture, 1);
    }
    return (stop);
}
