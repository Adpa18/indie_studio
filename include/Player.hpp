//
// Player.hpp for Player in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 09:36:14 2016 Victor Gouet
// Last update Wed Apr 27 15:18:44 2016 Victor Gouet
//

#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include "ACharacter.hpp"
# include <map>

class	Player	: public ACharacter
{
private:
    bool    KeyIsDown[irr::KEY_KEY_CODES_COUNT];
    std::map<irr::EKEY_CODE, irr::EKEY_ACTION> _keycodes;
    int     _player;
    irr::SEvent::SJoystickEvent  JoystickState;

public:
  Player(std::string const &name, irr::core::vector3df const &pos, std::string const &mesh,
      int player// , std::map<irr::EKEY_CODE
	 // , irr::EKEY_ACTION> keycodes
	 );
  virtual ~Player();

// public:
//   virtual bool  OnEvent(const irr::SEvent& event);
//   virtual bool  IsKeyDown(irr::EKEY_CODE keyCode) const;
//   const irr::SEvent::SJoystickEvent &GetJoystickState(void) const;
};

#endif
