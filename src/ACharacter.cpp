//
// ACharacter.cpp for ACHARACTER in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 09:43:11 2016 Victor Gouet
// Last update Mon May  9 13:42:19 2016 Victor Gouet
//

// #include "Collider.hpp"
#include "ACharacter.hpp"
#include "BombFactory.hpp"
#include <iostream>
#include <BomberMap.hpp>

struct SMD3AnimationType
{
	irr::s32 begin;
	irr::s32 end;
	irr::s32 fps;
};

static const SMD3AnimationType MD3AnimationTypeList[3] =
{
	{  0,  96,  25}, // IDLE
	{ 97,  216, 20}, // RUN
	{ 217,  247,  25}, // ATTACK
};

ACharacter::ACharacter(std::string const &name, irr::core::vector2df const &pos,
		       std::string const &mesh, std::string const &texture, int player)
  : AGameObject(pos, mesh, texture, AGameObject::CHARACTER),
    _name(name), _player(player)
{
    bombPosed = false;
    _arrived = true;
    _last_act = irr::core::vector2df(0, 0);
    anime = irr::scene::EMAT_STAND;
  moveSpeed = BASICSPEED;
  then = IrrlichtController::getDevice()->getTimer()->getTime();
  _bombContainer = BombFactory::CreateBombContainer<FireBomb>();
   BombFactory::AddBomb<FireBomb>(*_bombContainer);
   BombFactory::AddBomb<FireBomb>(*_bombContainer);
   BombFactory::AddBomb<FireBomb>(*_bombContainer);
  setMD3Animation(MD3_ANIMATION::STAY);
}

ACharacter::~ACharacter()
{
}

void                    ACharacter::dead()
{
}

bool			ACharacter::isDestructible() const
{
  return (false);
}

void			ACharacter::exploseHisBomb()
{
  _bombContainer->bombExplose();
}

void			ACharacter::setMoveSpeed(double speed)
{
  this->moveSpeed = speed;
}

void ACharacter::setMD3Animation(MD3_ANIMATION anim)
{
  (*this)->setFrameLoop(MD3AnimationTypeList[anim].begin, MD3AnimationTypeList[anim].end);
  (*this)->setAnimationSpeed(MD3AnimationTypeList[anim].fps);
}


std::string const &	ACharacter::getName() const
{
  return (_name);
}

double		ACharacter::getMoveSpeed() const
{
  return (moveSpeed);
}

void			ACharacter::setName(const std::string &string)
{
  _name = string;
  (*this)->setName(string.c_str());
}

void            ACharacter::action(ACTION act)
{
    bool			stand = true;
    const irr::u32 now = IrrlichtController::getDevice()->getTimer()->getTime();
    this->frameDeltaTime = (irr::f32)(now - this->then) / 1000.f;

    if (_arrived || act == BOMB)
    {
        switch (act) {
            case DOWN:
                bombPosed = false;
                stand = false;
                _arrived = false;
                (*this)->setRotation(irr::core::vector3df(0, 0, 0));
                _last_act = irr::core::vector2df(0, -1);
                break;
            case UP:
                bombPosed = false;
                stand = false;
                _arrived = false;
                (*this)->setRotation(irr::core::vector3df(0, 180, 0));
                _last_act = irr::core::vector2df(0, 1);
                break;
            case LEFT:
                bombPosed = false;
                stand = false;
                _arrived = false;
                (*this)->setRotation(irr::core::vector3df(0, 90, 0));
                _last_act = irr::core::vector2df(-1, 0);
                break;
            case RIGHT:
                bombPosed = false;
                stand = false;
                _arrived = false;
                (*this)->setRotation(irr::core::vector3df(0, -90, 0));
                _last_act = irr::core::vector2df(1, 0);
                break;
            case BOMB:
                if (!bombPosed)
                    this->putBomb();
                bombPosed = true;
                break;
            default:
                bombPosed = false;
                _arrived = true;
                break;
        }
    }
    if (!_arrived)
    {
        stand = false;
        this->moveTo(_last_act);
    }
    if (stand && anime != irr::scene::EMAT_STAND)  {
        setMD3Animation(ACharacter::MD3_ANIMATION::STAY);
        anime = irr::scene::EMAT_STAND;
    } else if (!stand && anime != irr::scene::EMAT_RUN) {
        setMD3Animation(ACharacter::MD3_ANIMATION::RUN);
        anime = irr::scene::EMAT_RUN;
    }
    then = now;
}

void            ACharacter::moveTo(irr::core::vector2df const &dir)
{
    std::vector<AGameObject*>   objs = BomberMap::getMap()->getObjsFromVector2(this->getMapPos() + dir);
    AGameObject::Type           type;

    for (std::vector<AGameObject*>::const_iterator it = objs.begin(); it != objs.end(); ++it) {
        type = (*it)->getType();
        if (type != AGameObject::CHARACTER) {
            _arrived = true;
            return;
        }
    }
    float   distance = this->getRealPos().getDistanceFrom(this->getMapPos() + dir);

    if (distance < 0.2) {
        _arrived = true;
        this->setPos(this->getMapPos() + dir);
        return;
    }
    (*this)->setPosition(irr::core::vector3df((*this)->getPosition().X + dir.X * frameDeltaTime * 100, 0, (*this)->getPosition().Z + dir.Y * frameDeltaTime * 100));
}

void			ACharacter::putBomb()
{
  ABomb			*bomb;

  if ((bomb = _bombContainer->getBomb()))
    {
      *bomb << this->getMapPos();
    }
}
