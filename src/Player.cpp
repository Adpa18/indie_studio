//
// Player.cpp for Player in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 09:43:11 2016 Victor Gouet
// Last update Wed Apr 27 17:09:32 2016 Victor Gouet
//

#include "../include/Player.hpp"
#include <iostream>

Player::Player(std::string const &name, irr::core::vector3df const &pos,
	       std::string const &mesh, int player,
	       EventGame const &eventGame,
	       std::map<ACharacter::ACTION, irr::EKEY_CODE> const &keycodes)
  : ACharacter(name, pos, mesh),
    _player(player), _eventGame(eventGame), _keycodes(keycodes), _dir(IrrlichtController::RIGHT)
{
  anime = irr::scene::EMAT_STAND;
    (*this)->setName(name.c_str());
}

Player::~Player()
{
}

void		Player::compute()
{
  bool			stand = true;

  const irr::u32 now = IrrlichtController::getDevice()->getTimer()->getTime();
  const irr::f32 frameDeltaTime = (irr::f32)(now - then) / 1000.f;
  irr::f32 moveHorizontal = 0.f;
  irr::f32 moveVertical = 0.f;
  then = now;

  irr::core::vector3df nodePosition = (*this)->getPosition();

  // Joystick
  const irr::SEvent::SJoystickEvent &joystickData = _eventGame.GetJoystickState(this->_player);

	if (_eventGame.isAvaibleJoystick(this->_player)) {
		const irr::u16 povDegrees = joystickData.POV / 100;
		const irr::f32 DEAD_ZONE = 0.05f;
		moveHorizontal = (irr::f32)joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_X] / 32767.f;
		if(fabs(moveHorizontal) < DEAD_ZONE) {
			moveHorizontal = 0.f;
		}
		moveVertical = (irr::f32)joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_Y] / -32767.f;
		if(fabs(moveVertical) < DEAD_ZONE) {
			moveVertical = 0.f;
		}
		if (povDegrees < 360) {
			if(povDegrees > 0 && povDegrees < 180) {
				moveHorizontal = 1.f;
			} else if (povDegrees > 180) {
				moveHorizontal = -1.f;
			}
			if(povDegrees > 90 && povDegrees < 270) {
				moveVertical = -1.f;
			} else if (povDegrees > 270 || povDegrees < 90) {
				moveVertical = +1.f;
			}
		}
		// nodePosition.X += getMoveSpeed() * frameDeltaTime * moveHorizontal;
		// nodePosition.Z += getMoveSpeed() * frameDeltaTime * moveVertical;
	} else {
		// Arrows
		if (_eventGame.IsKeyDown(this->_keycodes.find(ACharacter::ACTION::DOWN)->second)) {
			moveVertical = -1.0f;
		} else if (_eventGame.IsKeyDown(this->_keycodes.find(ACharacter::ACTION::UP)->second)) {
			moveVertical = 1.0f;
		} else if (_eventGame.IsKeyDown(this->_keycodes.find(ACharacter::ACTION::LEFT)->second)) {
			moveHorizontal = -1.0f;
		} else if (_eventGame.IsKeyDown(this->_keycodes.find(ACharacter::ACTION::RIGHT)->second)) {
			moveHorizontal = 1.0f;
		}
	}
	if (moveHorizontal < 0.0f) {
		stand = false;
        (*this)->setRotation(irr::core::vector3df(0, 180, 0));
		this->_dir = IrrlichtController::LEFT;
		if (this->collid((*this)->getPosition(), IrrlichtController::LEFT) == -1) {
			nodePosition.X -= getMoveSpeed() * frameDeltaTime;
		}
	} else if (moveHorizontal > 0.0f) {
		stand = false;
        (*this)->setRotation(irr::core::vector3df(0, 0, 0));
		this->_dir = IrrlichtController::RIGHT;
		if (this->collid((*this)->getPosition(), IrrlichtController::RIGHT) == -1) {
			nodePosition.X += getMoveSpeed() * frameDeltaTime;
		}
	} else if (moveVertical > 0.0f) {
		stand = false;
        (*this)->setRotation(irr::core::vector3df(0, -90, 0));
		this->_dir = IrrlichtController::UP;
		if (this->collid((*this)->getPosition(), IrrlichtController::UP) == -1) {
			nodePosition.Z += getMoveSpeed() * frameDeltaTime;
		}
	} else if (moveVertical < 0.0f) {
		stand = false;
        (*this)->setRotation(irr::core::vector3df(0, 90, 0));
		this->_dir = IrrlichtController::DOWN;
		if (this->collid((*this)->getPosition(), IrrlichtController::DOWN) == -1) {
			nodePosition.Z -= getMoveSpeed() * frameDeltaTime;
		}
	}

  if (stand && anime != irr::scene::EMAT_STAND)
    {
      (*this)->setMD2Animation(irr::scene::EMAT_STAND);
      anime = irr::scene::EMAT_STAND;
    }
  else if (!stand && anime != irr::scene::EMAT_RUN)
    {
      (*this)->setMD2Animation(irr::scene::EMAT_RUN);
      anime = irr::scene::EMAT_RUN;
    }
	(*this)->setPosition(nodePosition);
}
