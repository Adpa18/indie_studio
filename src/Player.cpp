//
// Player.cpp for Player in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 09:43:11 2016 Victor Gouet
// Last update Thu May  5 15:24:24 2016 Victor Gouet
//

#include "../include/Player.hpp"
#include <iostream>

Player::Player(std::string const &name, irr::core::vector2di const &pos,
	       std::string const &mesh, std::string const &texture, int player,
	       EventGame const &eventGame)
  : ACharacter(name, pos, mesh, texture, player), _eventGame(eventGame)
{
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
    ACharacter::ACTION  act = ACharacter::IDLE;
  // Joystick
  this->exploseHisBomb();
  if (this->_joystick) {
//		const irr::SEvent::SJoystickEvent &joystickData = this->_joystick->getData();
//		const irr::u16 povDegrees = joystickData.POV / 100;
//		const irr::f32 DEAD_ZONE = 0.05f;
//		moveHorizontal = (irr::f32)joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_X] / 32767.f;
//		if(fabs(moveHorizontal) < DEAD_ZONE) {
//			moveHorizontal = 0.f;
//		}
//		moveVertical = (irr::f32)joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_Y] / -32767.f;
//		if(fabs(moveVertical) < DEAD_ZONE) {
//			moveVertical = 0.f;
//		}
//		if (povDegrees < 360) {
//			if(povDegrees > 0 && povDegrees < 180) {
//				moveHorizontal = 1.f;
//			} else if (povDegrees > 180) {
//				moveHorizontal = -1.f;
//			}
//			if(povDegrees > 90 && povDegrees < 270) {
//				moveVertical = -1.f;
//			} else if (povDegrees > 270 || povDegrees < 90) {
//				moveVertical = +1.f;
//			}
//		}
		// nodePosition.X += getMoveSpeed() * frameDeltaTime * moveHorizontal;
		// nodePosition.Z += getMoveSpeed() * frameDeltaTime * moveVertical;
	} else {
		// KeysCode
		if (_eventGame.IsKeyDown(this->_keycodes.find(ACharacter::ACTION::DOWN)->second)) {
			act = ACharacter::ACTION::DOWN;
		} else if (_eventGame.IsKeyDown(this->_keycodes.find(ACharacter::ACTION::UP)->second)) {
            act = ACharacter::ACTION::UP;
		} else if (_eventGame.IsKeyDown(this->_keycodes.find(ACharacter::ACTION::LEFT)->second)) {
            act = ACharacter::ACTION::LEFT;
		} else if (_eventGame.IsKeyDown(this->_keycodes.find(ACharacter::ACTION::RIGHT)->second)) {
            act = ACharacter::ACTION::RIGHT;
		}
        if (_eventGame.IsKeyDown(this->_keycodes.find(ACharacter::ACTION::BOMB)->second)) {
            act = ACharacter::ACTION::BOMB;
        }
	}
    this->action(act);
}
