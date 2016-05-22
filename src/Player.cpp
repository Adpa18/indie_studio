//
// Player.cpp for Player in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 09:43:11 2016 Victor Gouet
// Last update Sun May 22 17:23:22 2016 Victor Gouet
//

#include "../include/ACharacter.hpp"
#include "../include/Player.hpp"
#include "../include/MineBomb.hpp"
#include <iostream>

Player::Player(std::string const &name, irr::core::vector2df const &pos,
	       std::string const &mesh, std::string const &texture, int player,
	       EventGame const &eventGame)
  : ACharacter(name, pos, mesh, texture, player), _eventGame(eventGame)
{
   (*this)->setName(name.c_str());
    this->_joystick = NULL;
    keyController = NULL;
    if ((this->_joystick = _eventGame.GetAvaibleJoystick()) == NULL) {
      keyController = _eventGame.GetAvaibleKeycodes();
      if (keyController)
      	this->_keycodes = keyController->getKeycodes();
    }
}

Player::~Player()
{
  if (this->_joystick)
    this->_joystick->stopUseIt();
  if (this->keyController)
    this->keyController->stopUseIt();
}

void		Player::compute()
{
    ACharacter::ACTION  act = ACharacter::IDLE;
  // Joystick
  // this->exploseHisBomb();
  if (this->_joystick) {
      act = this->_joystick->getDirAxis(MotionController::LEFT_JOYSTICK);
      if (this->_joystick->IsButtonPressed(MotionController::CROSS)) {
          act = ACharacter::ACTION::BOMB;
      }
      // PAS SET POUR LE ACharacter::ACTION::ACT !!
      
  } else {
    // KeysCode
    // if (_eventGame.IsKeyDownOneTime(irr::EKEY_CODE::KEY_KEY_H))
    //   {
    // 	MineBomb *bomb = new MineBomb(this->getID());
    // 	*bomb << this->getMapPos();
    //   }
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
    if (_eventGame.IsKeyDownOneTime(this->_keycodes.find(ACharacter::ACTION::ACT)->second)) {
      act = ACharacter::ACTION::ACT;
    }
  }
  this->action(act);
}
