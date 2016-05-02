/*
** EventGame.cpp for cpp_indie_studio
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Apr 27 15:16:31 2016 Adrien WERY
** Last update	Sat Apr 30 01:04:43 2016 Adrien WERY
*/

#include "../include/EventGame.hpp"
#include <iostream>

const std::vector<std::map<ACharacter::ACTION, irr::EKEY_CODE>> EventGame::_keycodes({{
    {ACharacter::LEFT, irr::KEY_LEFT},
    {ACharacter::RIGHT, irr::KEY_RIGHT},
    {ACharacter::UP, irr::KEY_UP},
      {ACharacter::DOWN, irr::KEY_DOWN},
	{ACharacter::BOMB, irr::KEY_SPACE}
},{
    {ACharacter::LEFT, irr::KEY_KEY_Q},
    {ACharacter::RIGHT, irr::KEY_KEY_D},
    {ACharacter::UP, irr::KEY_KEY_Z},
    {ACharacter::DOWN, irr::KEY_KEY_S}
}});

EventGame::EventGame()
{
    irr::core::array<irr::SJoystickInfo>    joystickInfo;

    if (IrrlichtController::getDevice()->activateJoysticks(joystickInfo)) {
        for (size_t i = 0; i < joystickInfo.size(); i++) {
            if (joystickInfo[i].Axes > 0 && joystickInfo[i].Buttons > 0) {
                this->_joysticks[i] = new MotionController(joystickInfo[i]);
            }
        }
    }
    for (std::vector<std::map<ACharacter::ACTION, irr::EKEY_CODE>>::const_iterator it = this->_keycodes.begin(); it != this->_keycodes.end(); ++it) {
        this->_keymaps.push_back(new KeysController(*it));
    }
  for (irr::u32 i=0; i < irr::KEY_KEY_CODES_COUNT; ++i) {
      KeyIsDown[i] = false;
  }
}

EventGame::~EventGame()
{

}

bool 	EventGame::OnEvent(const irr::SEvent &event)
{
  if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
    KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
  }
  if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT && this->_joysticks[event.JoystickEvent.Joystick]) {
      this->_joysticks[event.JoystickEvent.Joystick]->setData(event.JoystickEvent);
  }
  return (false);
}

bool 	EventGame::IsKeyDown(irr::EKEY_CODE keyCode) const
{
	return (KeyIsDown[keyCode]);
}

const MotionController  *EventGame::GetAvaibleJoystick() const
{
    for (std::map<int, MotionController *>::const_iterator it = this->_joysticks.begin(); it != this->_joysticks.end(); ++it) {
        if (!it->second->isUsed()) {
            it->second->useIt();
            return (it->second);
        }
    }
    return (NULL);
}

const KeysController    *EventGame::GetAvaibleKeycodes() const
{
    for (std::vector<KeysController *>::const_iterator it = this->_keymaps.begin(); it != this->_keymaps.end(); ++it) {
        if (!(*it)->isUsed()) {
            (*it)->useIt();
            return (*it);
        }
    }
    return (NULL);
}
