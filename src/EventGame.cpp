/*
** EventGame.cpp for cpp_indie_studio
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Apr 27 15:16:31 2016 Adrien WERY
** Last update	Wed Apr 27 17:32:14 2016 Adrien WERY
*/

#include "../include/EventGame.hpp"
#include <iostream>

EventGame::EventGame()
{
  for (irr::u32 i=0; i < irr::KEY_KEY_CODES_COUNT; ++i)
    KeyIsDown[i] = false;
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
    this->JoystickState = event.JoystickEvent;
  }
  return (false);
}

const irr::SEvent::SJoystickEvent &EventGame::GetJoystickState(void) const
{
  return (this->JoystickState);
}

bool 	EventGame::IsKeyDown(irr::EKEY_CODE keyCode) const
{
	return (KeyIsDown[keyCode]);
}

irr::SJoystickInfo  EventGame::getJoystick(unsigned int id) const
{
    irr::core::array<irr::SJoystickInfo> joystickInfo;

    if(IrrlichtController::getDevice()->activateJoysticks(joystickInfo)) {
        if (id < joystickInfo.size()) {
            return (joystickInfo[id]);
        }
    }
    return (irr::SJoystickInfo());
}
