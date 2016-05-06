//
// ACharacter.cpp for ACHARACTER in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 09:43:11 2016 Victor Gouet
// Last update Thu May  5 15:23:50 2016 Victor Gouet
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


ACharacter::ACharacter(std::string const &name, irr::core::vector2di const &pos,
		       std::string const &mesh, std::string const &texture, int player)
  : AGameObject(pos, mesh, texture, AGameObject::CHARACTER),
    _name(name), _player(player)
{
    anime = irr::scene::EMAT_STAND;
  moveSpeed = BASICSPEED;
  then = IrrlichtController::getDevice()->getTimer()->getTime();
  // this->setCollider(new Collider(AGameObject::CHARACTER));
  _bombContainer = BombFactory::CreateBombContainer<FireBomb>();
  // BombFactory::AddBomb<FireBomb>(*_bombContainer);
  setMD3Animation(MD3_ANIMATION::STAY);
}

ACharacter::~ACharacter()
{
}

void			ACharacter::exploseHisBomb()
{
  _bombContainer->bombExplose();
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
    const irr::f32 frameDeltaTime = (irr::f32)(now - then) / 1000.f;

    switch (act) {
        case DOWN:
            stand = false;
            (*this)->setRotation(irr::core::vector3df(0, 0, 0));
            this->moveTo(this->getPos() + irr::core::vector2di(0, -1));
//            this->_dir = IrrlichtController::DOWN;
//            if (!this->collid(nodePosition, IrrlichtController::DOWN)) {
//                nodePosition.Z -= getMoveSpeed() * frameDeltaTime;
//            }
            break;
        case UP:
            stand = false;
            (*this)->setRotation(irr::core::vector3df(0, 180, 0));
            this->moveTo(this->getPos() + irr::core::vector2di(0, 1));
//            this->_dir = IrrlichtController::UP;
//            if (!this->collid(nodePosition, IrrlichtController::UP)) {
//                nodePosition.Z += getMoveSpeed() * frameDeltaTime;
//            }
            break;
        case LEFT:
            stand = false;
            (*this)->setRotation(irr::core::vector3df(0, 90, 0));
            this->moveTo(this->getPos() + irr::core::vector2di(-1, 0));
//            this->_dir = IrrlichtController::LEFT;
//            if (!this->collid(nodePosition, IrrlichtController::LEFT)) {
//                nodePosition.X -= getMoveSpeed() * frameDeltaTime;
//            }
            break;
        case RIGHT:
            stand = false;
                (*this)->setRotation(irr::core::vector3df(0, -90, 0));
                this->moveTo(this->getPos() + irr::core::vector2di(1, 0));
//                this->_dir = IrrlichtController::RIGHT;
//                if (!this->collid(nodePosition, IrrlichtController::RIGHT)) {
//                    nodePosition.X += getMoveSpeed() * frameDeltaTime;
//                }
            break;
        case BOMB:
            this->putBomb();
            break;
        default:
            break;
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

void            ACharacter::moveTo(irr::core::vector2di const &pos)
{
    std::vector<AGameObject*>   objs = BomberMap::getMap()->getObjsFromVector2(pos);
    AGameObject::Type           type;

    for (std::vector<AGameObject*>::const_iterator it = objs.begin(); it != objs.end(); ++it) {
        type = (*it)->getType();
        if (type != AGameObject::CHARACTER) {
            return;
        }
    }
    this->setPos(pos);
}


void			ACharacter::putBomb()
{
  ABomb			*bomb;

  if ((bomb = _bombContainer->getBomb()))
    {
      *bomb << this->getPos();
    }
}
