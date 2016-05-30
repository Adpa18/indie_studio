//
// Bomb.cpp for BOMB in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Thu Apr 28 16:25:11 2016 Victor Gouet
// Last update Wed May 25 22:40:28 2016 Victor Gouet
//

#include <iostream>
#include <unistd.h>
#include <GameManager.hpp>
#include "../../include/ABomb.hpp"
#include "../../include/BombFactory.hpp"
#include "../../include/BomberMap.hpp"
#include "../../include/GameObjectTimeContainer.hpp"
#include "SoundManager.hpp"

ABomb::ABomb(std::string const &mesh, std::string const &texture, double timeout, int id) :
  AGameObject(irr::core::vector2df(-1000, -1000),
	      mesh, texture, AGameObject::BOMB),
  mesh(mesh), texture(texture), timeout(timeout), characterId(id)
{
  _arrived = true;
  then = IrrlichtController::getDevice()->getTimer()->getTime();
  dir = irr::core::vector2df(0, 0);
  use = false;
  (*this)->setVisible(false);
  _power = 1;
  __active = false;
  (*this)->setScale(irr::core::vector3df(1, 1, 1));
}

ABomb::ABomb(ABomb const *other)
  : AGameObject(irr::core::vector2df(-1000, -1000),
		other->mesh,
		other->texture, AGameObject::BOMB)
{
  *this = other;
}

ABomb	&ABomb::operator=(ABomb const *other)
{
  // timeout = other->timeout;
  characterId = other->characterId;
  _arrived = true;
  then = IrrlichtController::getDevice()->getTimer()->getTime();
  dir = irr::core::vector2df(0, 0);
  use = false;
  (*this)->setVisible(false);
  this->_power = other->_power;
  this->__active = false;
  this->mesh = other->mesh;
  this->texture = other->texture;
  return (*this);
}

ABomb::~ABomb()
{
   BomberMap::getMap()->remove(this);
}

double		ABomb::getTimeOut() const
{
  return (this->timeout);
}

void		ABomb::serialize(irr::io::IXMLWriter *) const
{
}

void			ABomb::setVelocity(irr::core::vector2df const &_dir)
{
  dir = _dir;
  _arrived = false;
}

void			ABomb::move(double speed)
{
  float   distance = this->getRealPos().getDistanceFrom(this->getMapPos() + dir);
  const irr::u32 now = IrrlichtController::getDevice()->getTimer()->getTime();
  this->frameDeltaTime = (irr::f32)(now - this->then) / 1000.f;

  if (!_arrived)
    {
      std::vector<AGameObject*>   objs = BomberMap::getMap()->getObjsFromVector2(this->getMapPos() + dir);
      for (std::vector<AGameObject*>::iterator it = objs.begin(), end = objs.end() ; it != end ; ++it)
	{
	  if ((*it)->getType() == AGameObject::BLOCK
	      || (*it)->getType() == AGameObject::OTHER
	      || (*it)->getType() == AGameObject::CHARACTER)
	    _arrived = true;
	}
      if (use && !_arrived)
	{
	  if (distance < 0.2 || distance > 1)
	    {
	      std::vector<AGameObject*>   objs = BomberMap::getMap()->getObjsFromVector2(this->getMapPos() + dir + dir);
	      if (objs.size() > 0)
		_arrived = true;
	      this->setPos(this->getMapPos() + dir);
	      then = now;
	      return;
	    }
	  (*this)->setPosition(irr::core::vector3df((*this)->getPosition().X + dir.X * frameDeltaTime * speed, 0, (*this)->getPosition().Z + dir.Y * frameDeltaTime * speed));
	}
    }
  then = now;
}

void			ABomb::updateTimeOut()
{
  (*this)->setScale((*this)->getScale() + 0.008);
  move();
}

void                        ABomb::dead()
{
  if (use)
    {
      SoundManager::getManager()->play("explosion.wav", (*this)->getID());
      _arrived = true;
      use = false;
      willExplose();
      disable();
    }
  (*this)->setScale(irr::core::vector3df(1, 1, 1));
}

bool			ABomb::isDestructible() const
{
  return (false);
}

bool			ABomb::isUse() const
{
  return (use);
}

void		ABomb::disable()
{
  this->setPos(irr::core::vector2df(-1000, -1000));
  setTimeOut(-1);
}

void			ABomb::operator<<(irr::core::vector2df
					  const &pos)
{
  (*this)->setScale(irr::core::vector3df(1, 1, 1));
  then = IrrlichtController::getDevice()->getTimer()->getTime();
  (*this)->setVisible(true);
  use = true;
  this->setTimeOut(timeout);
  this->setPos(pos);
//   irr::core::vector2df        mpos = this->getMapPos();
//   for (int power = 1; power <= this->_power; ++power)
//      BomberMap::getMap()->setDangerAtPos(mpos + irr::core::vector2df(-power, 0), AGameObject::Type::BOOM);
//   for (int power = 1; power <= this->_power; ++power)
//      BomberMap::getMap()->setDangerAtPos(mpos + irr::core::vector2df(power, 0), AGameObject::Type::BOOM);
//   for (int power = 1; power <= this->_power; ++power)
//      BomberMap::getMap()->setDangerAtPos(mpos + irr::core::vector2df(0, -power), AGameObject::Type::BOOM);
//   for (int power = 1; power <= this->_power; ++power)
//      BomberMap::getMap()->setDangerAtPos(mpos + irr::core::vector2df(0, power), AGameObject::Type::BOOM);
//    BomberMap::getMap()->setDangerAtPos(mpos, AGameObject::Type::BOMB);
//   BomberMap::getMap()->displayDangerMap();
}

void			ABomb::setPower(int power)
{
  if (_power > 5)
    return ;
  _power = power;
}

int			ABomb::getPower() const
{
  return (_power);
}
