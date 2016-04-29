//
// Player.hpp for Player in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 09:36:14 2016 Victor Gouet
// Last update Fri Apr 29 17:56:06 2016 Victor Gouet
//

#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include "EventGame.hpp"
# include "ACharacter.hpp"
# include "MotionController.hpp"
# include <map>

class	Player	: public ACharacter
{
private:
  int     _player;
  EventGame	const &					_eventGame;
  int							    anime;
  std::map<ACharacter::ACTION, irr::EKEY_CODE>  _keycodes;
  const MotionController            *_joystick;
  IrrlichtController::Direction     _dir;

public:
  Player(std::string const &name, irr::core::vector3df const &pos,
	 std::string const &mesh, int player, EventGame const &eventGame);
  virtual ~Player();

public:
  virtual void		compute();
};

#endif
