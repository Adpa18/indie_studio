/*
** EventGame.cpp for cpp_indie_studio
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Apr 27 15:16:31 2016 Adrien WERY
** Last update	Thu Apr 28 22:22:47 2016 Adrien WERY
*/

#include "../include/EventGame.hpp"
#include <iostream>

EventGame::EventGame()
{
    irr::core::array<irr::SJoystickInfo>    joystickInfo;

    IrrlichtController::getDevice()->activateJoysticks(joystickInfo);
    for (size_t i = 0; i < joystickInfo.size(); i++) {
        this->_joystickStates.push_back(irr::SEvent::SJoystickEvent());
    }
    _nbJoystick = joystickInfo.size();
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
  if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT) {
      this->_joystickStates[event.JoystickEvent.Joystick] = event.JoystickEvent;
  }
  return (false);
}

const irr::SEvent::SJoystickEvent &EventGame::GetJoystickState(unsigned int id) const
{
  return (this->_joystickStates[id]);
}

bool 	EventGame::IsKeyDown(irr::EKEY_CODE keyCode) const
{
	return (KeyIsDown[keyCode]);
}
