//
// Player.cpp for Player in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 09:43:11 2016 Victor Gouet
// Last update Wed Apr 27 15:58:05 2016 Victor Gouet
//

#include "../include/Player.hpp"
#include <iostream>

Player::Player(std::string const &name, irr::core::vector3df const &pos,
	       std::string const &mesh, int player,
	       EventGame const &eventGame,
	       std::map<irr::EKEY_CODE, irr::EKEY_CODE> const &keycodes)
  : ACharacter(name, pos, mesh),
    _player(player), _eventGame(eventGame), _keycodes(keycodes)
{

}

Player::~Player()
{
}

void		Player::compute()
{
  
  if (_eventGame.IsKeyDown(irr::KEY_KEY_Z))
    {
      std::cout << "Z touch" << std::endl;
      //sydney->setPosition(sydney->getPosition() + 0.05);
    }
  if (_eventGame.IsKeyDown(irr::KEY_KEY_S))
    {
      std::cout << "S touch" << std::endl;
      //sydney->setPosition(sydney->getPosition() + 0.05);
    }
}
