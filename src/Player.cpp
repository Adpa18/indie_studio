//
// Player.cpp for Player in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 09:43:11 2016 Victor Gouet
// Last update Wed Apr 27 17:04:10 2016 Victor Gouet
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
  static int anime = irr::scene::EMAT_STAND;
  bool			stand = true;

  const irr::u32 now = IrrlichtController::getDevice()->getTimer()->getTime();
  const irr::f32 frameDeltaTime = (irr::f32)(now - then) / 1000.f;
  then = now;

  irr::core::vector3df nodePosition = (*this)->getPosition();
  if (_eventGame.IsKeyDown(irr::KEY_DOWN))
    {
      nodePosition.Z -= getMouveSpeed() * frameDeltaTime;
      stand = false;
      (*this)->setRotation(irr::core::vector3df(0, 90, 0));
    }
  else if (_eventGame.IsKeyDown(irr::KEY_UP))
    {
      stand = false;
      nodePosition.Z += getMouveSpeed() * frameDeltaTime;
      (*this)->setRotation(irr::core::vector3df(0, -90, 0));
    }

  if (_eventGame.IsKeyDown(irr::KEY_LEFT))
    {
      stand = false;
      nodePosition.X -= getMouveSpeed() * frameDeltaTime;
      (*this)->setRotation(irr::core::vector3df(0, 180, 0));
    }
  else if (_eventGame.IsKeyDown(irr::KEY_RIGHT))
    {
      stand = false;
      nodePosition.X += getMouveSpeed() * frameDeltaTime;
      (*this)->setRotation(irr::core::vector3df(0, 0, 0));
    }

  if (stand && anime != irr::scene::EMAT_STAND)
    {
      (*this)->setMD2Animation(irr::scene::EMAT_STAND);
      anime = irr::scene::EMAT_STAND;
    }
  else if (!stand && anime != irr::scene::EMAT_RUN)
    {
      (*this)->setMD2Animation(irr::scene::EMAT_RUN);
      anime = irr::scene::EMAT_RUN;
    }
  
  

  (*this)->setPosition(nodePosition);
}
