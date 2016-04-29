//
// ACharacter.cpp for ACHARACTER in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 09:43:11 2016 Victor Gouet
// Last update Fri Apr 29 18:43:43 2016 Victor Gouet
//

#include "../include/ACharacter.hpp"
#include "../include/BombFactory.hpp"

ACharacter::ACharacter(std::string const &name, irr::core::vector3df const &pos,
		       std::string const &mesh) : AGameObject(pos, mesh), _name(name)
{
  moveSpeed = BASICSPEED;
  then = IrrlichtController::getDevice()->getTimer()->getTime();
  this->addCollider(new Collider());
  _bombContainer = BombFactory::CreateBombContainer<FireBomb>();
  // BombFactory::AddBomb<FireBomb>(*_bombContainer);
}

ACharacter::~ACharacter()
{
}

std::string const &	ACharacter::getName() const
{
  return (_name);
}

double		ACharacter::getMoveSpeed() const
{
  return (moveSpeed);
}

// void 		ACharacter::move(int x, int y, int z)
// {
// 	(*this)->setPosition((*this)->getPosition() + irr::core::vector3df(x * this->moveSpeed, y * this->moveSpeed, z * this->moveSpeed));
// }

// void 		ACharacter::move(int x, int y)
// {
// 	this->move(x, y, 0);
// }
void			ACharacter::setName(const std::string &string)
{
  _name = string;
  (*this)->setName(string.c_str());
}

void			ACharacter::putBomb()
{
  ABomb			*bomb;

  if ((bomb = _bombContainer->getBomb()))
    {
      *bomb << (*this)->getPosition();
    }
}
