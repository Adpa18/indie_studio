//
// Wall.cpp for WALL in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Apr 27 18:19:48 2016 Victor Gouet
// Last update Wed Apr 27 20:00:29 2016 Victor Gouet
//

#include "../include/Wall.hpp"

Wall::Wall(irr::core::vector3df const &pos, State state) // 1 caisseMetal
  : AGameObject(pos, state == Invicible ? "media/caisse" : "media/caisse"), _state(state)
{
  
}

Wall::~Wall()
{
  
}

Wall::State			Wall::getState() const
{
  return (_state);
}
