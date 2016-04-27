//
// Player.cpp for Player in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 09:43:11 2016 Victor Gouet
// Last update Wed Apr 27 09:52:38 2016 Victor Gouet
//

#include "../include/Player.hpp"

Player::Player(std::string const &name, irr::core::vector3df const &pos,
		       std::string const &mesh, int player,
			   std::map<irr::EKEY_CODE, irr::EKEY_ACTION> keycodes)
			   : AGameObject(pos, mesh), _keycodes(keycodes), _player(player)
{
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i) {
		KeyIsDown[i] = false;
	}
}

Player::~Player()
{

}

bool 	Player::OnEvent(const irr::SEvent &event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	}
	if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT && event.JoystickEvent.Joystick == this->_player) {
            this->JoystickState = event.JoystickEvent;
        }
	return (false);
}

const irr::SEvent::SJoystickEvent &Player::GetJoystickState(void) const
    {
        return (this->JoystickState);
    }

bool 	Player::IsKeyDown(irr::EKEY_CODE keyCode) const
{
	return (KeyIsDown[keyCode]);
}
