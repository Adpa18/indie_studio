//
// Player.cpp for Player in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 09:43:11 2016 Victor Gouet
// Last update Sun May  1 19:09:16 2016 Victor Gouet
//

#include "../include/Player.hpp"
#include <iostream>

Player::Player(std::string const &name, irr::core::vector3df const &pos,
	       std::string const &mesh, std::string const &texture, int player,
	       EventGame const &eventGame)
  : ACharacter(name, pos, mesh, texture),
    _player(player), _eventGame(eventGame), _dir(IrrlichtController::RIGHT)
{
  anime = irr::scene::EMAT_STAND;
    (*this)->setName(name.c_str());
	if ((this->_joystick = _eventGame.GetAvaibleJoystick()) == NULL) {
		this->_keycodes = _eventGame.GetAvaibleKeycodes()->getKeycodes();
	}
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

  // irr::core::vector3df nodePosition = (*this)->getPosition();

  // Joystick
  if (this->_joystick) {
		const irr::SEvent::SJoystickEvent &joystickData = this->_joystick->getData();
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

		// PUT A BOMB

		// if (_eventGame.IsKeyDown(this->_keycodes.find(ACharacter::ACTION::BOMB)->second))
		//   {
		//     this->putBomb();
		//   }

	}
	if (moveHorizontal < 0.0f) {
		stand = false;
        (*this)->setRotation(irr::core::vector3df(0, 90, 0));
		this->_dir = IrrlichtController::LEFT;
		if (this->collid((*this)->getPosition(), IrrlichtController::LEFT) == -1) {
			// nodePosition.X -= getMoveSpeed() * frameDeltaTime;
		  goLeft();
		}
	} else if (moveHorizontal > 0.0f) {
		stand = false;
        (*this)->setRotation(irr::core::vector3df(0, -90, 0));
		this->_dir = IrrlichtController::RIGHT;
		if (this->collid((*this)->getPosition(), IrrlichtController::RIGHT) == -1) {
			// nodePosition.X += getMoveSpeed() * frameDeltaTime;
		  goRight();
		}
	} else if (moveVertical > 0.0f) {
		stand = false;
        (*this)->setRotation(irr::core::vector3df(0, 180, 0));
		this->_dir = IrrlichtController::UP;
		if (this->collid((*this)->getPosition(), IrrlichtController::UP) == -1) {
			// nodePosition.Z += getMoveSpeed() * frameDeltaTime;
		  goUp();
		}
	} else if (moveVertical < 0.0f) {
		stand = false;
        (*this)->setRotation(irr::core::vector3df(0, 0, 0));
		this->_dir = IrrlichtController::DOWN;
		if (this->collid((*this)->getPosition(), IrrlichtController::DOWN) == -1) {
			// nodePosition.Z -= getMoveSpeed() * frameDeltaTime;
		  goDown();
		}
	}
	else if (_eventGame.IsKeyDown(this->_keycodes.find(ACharacter::ACTION::BOMB)->second))
	  {
	    this->putBomb();
	  }

	// attack
	// 217 247

  if (stand && anime != irr::scene::EMAT_STAND)
    {
      //stand
      setMD3Animation(ACharacter::MD3_ANIMATION::STAY);
      anime = irr::scene::EMAT_STAND;
    }
  else if (!stand && anime != irr::scene::EMAT_RUN)
    {
      // run
      setMD3Animation(ACharacter::MD3_ANIMATION::RUN);
      anime = irr::scene::EMAT_RUN;
    }

  then = now;

  // (*this)->setPosition(nodePosition);
}
