//
// ACharacter.cpp for ACHARACTER in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 09:43:11 2016 Victor Gouet
// Last update Thu May  5 15:23:50 2016 Victor Gouet
//

#include "../include/ACharacter.hpp"
#include "../include/BombFactory.hpp"

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


ACharacter::ACharacter(std::string const &name, irr::core::vector3df const &pos,
		       std::string const &mesh, std::string const &texture)
  : AGameObject(pos, mesh, texture), _name(name)
{
  moveSpeed = BASICSPEED;
  then = IrrlichtController::getDevice()->getTimer()->getTime();
  this->addCollider(new Collider());
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

void			ACharacter::goLeft()
{
  const irr::u32 now = IrrlichtController::getDevice()->getTimer()->getTime();
  const irr::f32 frameDeltaTime = (irr::f32)(now - then) / 1000.f;
  // then = now;

  irr::core::vector3df nodePosition = (*this)->getPosition();

  nodePosition.X -= getMoveSpeed() * frameDeltaTime;

  (*this)->setPosition(nodePosition);
}

void			ACharacter::goRight()
{
 const irr::u32 now = IrrlichtController::getDevice()->getTimer()->getTime();
 const irr::f32 frameDeltaTime = (irr::f32)(now - then) / 1000.f;
 // then = now;

 irr::core::vector3df nodePosition = (*this)->getPosition();

 nodePosition.X += getMoveSpeed() * frameDeltaTime;

  (*this)->setPosition(nodePosition);
}

void			ACharacter::goDown()
{
 const irr::u32 now = IrrlichtController::getDevice()->getTimer()->getTime();
 const irr::f32 frameDeltaTime = (irr::f32)(now - then) / 1000.f;
 // then = now;

 irr::core::vector3df nodePosition = (*this)->getPosition();

  nodePosition.Z -= getMoveSpeed() * frameDeltaTime;

  (*this)->setPosition(nodePosition);
}

void			ACharacter::goUp()
{
 const irr::u32 now = IrrlichtController::getDevice()->getTimer()->getTime();
 const irr::f32 frameDeltaTime = (irr::f32)(now - then) / 1000.f;
 // then = now;

 irr::core::vector3df nodePosition = (*this)->getPosition();

  nodePosition.Z += getMoveSpeed() * frameDeltaTime;

  (*this)->setPosition(nodePosition);
}

void			ACharacter::putBomb()
{
  ABomb			*bomb;

  if ((bomb = _bombContainer->getBomb()))
    {
      *bomb << (*this)->getPosition();
    }
}
