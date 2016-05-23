//
// Player.hpp for Player in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 09:36:14 2016 Victor Gouet
// Last update Mon May 23 18:07:47 2016 Victor Gouet
//

#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include <map>
# include "EventGame.hpp"
# include "MotionController.hpp"

class	Player	: public ACharacter
{
private:
  EventGame	const &					_eventGame;
  std::map<ACharacter::ACTION, irr::EKEY_CODE>  _keycodes;
  const MotionController            *_joystick;
  const KeysController			*keyController;

public:
  Player(std::string const &name, irr::core::vector2df const &pos,
	 std::string const &mesh, std::string const &texture, int player,
	 EventGame const &eventGame = EventGame());
  virtual ~Player();

public:
  virtual void		compute();
  virtual void		serialize(irr::io::IXMLWriter *) const;
  // void            setMD3Animation(MD3_ANIMATION anim);
};

#endif
