/*
** EventGame.cpp for cpp_indie_studio
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Apr 27 15:16:31 2016 Adrien WERY
** Last update	Thu Apr 28 23:48:53 2016 Adrien WERY
*/

#include "../include/EventGame.hpp"
#include <iostream>

EventGame::EventGame()
{
    irr::core::array<irr::SJoystickInfo>    joystickInfo;

    if (IrrlichtController::getDevice()->activateJoysticks(joystickInfo)) {
        for (size_t i = 0; i < joystickInfo.size(); i++) {
            if (joystickInfo[i].Axes > 0 && joystickInfo[i].Buttons > 0) {
                this->_joysticks.push_back(irr::SEvent::SJoystickEvent());
                this->_isJoysticks[joystickInfo[i].Joystick] = true;
            } else {
                this->_isJoysticks[joystickInfo[i].Joystick] = false;
            }
        }
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
  if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT && this->_isJoysticks[event.JoystickEvent.Joystick]) {
      this->_joysticks[event.JoystickEvent.Joystick] = event.JoystickEvent;
  }
  return (false);
}

const irr::SEvent::SJoystickEvent   &EventGame::GetJoystickState(unsigned int id) const
{
    return (this->_joysticks[id]);
}

bool 	EventGame::IsKeyDown(irr::EKEY_CODE keyCode) const
{
	return (KeyIsDown[keyCode]);
}

bool    EventGame::isAvaibleJoystick(unsigned int id) const
{
    return (id < this->_joysticks.size());
}
