//
// Player.cpp for Player in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 09:43:11 2016 Victor Gouet
// Last update Wed Apr 27 15:18:57 2016 Victor Gouet
//

#include "../include/Player.hpp"

Player::Player(std::string const &name, irr::core::vector3df const &pos,
	       std::string const &mesh, int player
	       )
  : ACharacter(name, pos, mesh),
    _player(player)
{

}

Player::~Player()
{

}
