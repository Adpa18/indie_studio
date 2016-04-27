//
// Player.hpp for Player in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 09:36:14 2016 Victor Gouet
// Last update Wed Apr 27 15:57:19 2016 Victor Gouet
//

#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include "EventGame.hpp"
# include "ACharacter.hpp"
# include <map>

class	Player	: public ACharacter
{
private:
  int     _player;
  EventGame	const &					_eventGame;
  std::map<irr::EKEY_CODE, irr::EKEY_CODE> const &	_keycodes;

public:
  Player(std::string const &name, irr::core::vector3df const &pos,
	 std::string const &mesh, int player, EventGame const &eventGame,
	 std::map<irr::EKEY_CODE, irr::EKEY_CODE> const &keycodes);
  virtual ~Player();

public:
  virtual void		compute();
};

#endif
