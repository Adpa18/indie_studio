//
// Wall.cpp for WALL in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Apr 27 18:19:48 2016 Victor Gouet
// Last update Fri May 20 18:31:59 2016 Victor Gouet
//

#include <iostream>
#include "../include/Wall.hpp"
#include "../include/Texture.hpp"

const std::map<Wall::State, std::string>  Wall::_types = {
        {Invicible, "cubeIndestructible"},
        {Destructible, "cubeDestructible"},
        {Edge, "edge"},
};

// const std::map<int, std::string>  Wall::_wallSmallMap = {
//         {0, "cubeIndestructible"},
//         {1, "cubeDestructible"},
//         {2, "edge"},
// };

Wall::Wall(irr::core::vector2df const &pos, State state)
  : AGameObject(pos, BomberManTexture::getModel(_types.find(state)->second).mesh,
                BomberManTexture::getModel(_types.find(state)->second).texture,
                (state == Destructible) ? OTHER : BLOCK), _state(state)
{
    (*this)->setScale(irr::core::vector3df(0.8f, 0.8f, 0.8f));
}

Wall::Wall(irr::core::vector2df const &pos, State state,
	   std::string const &mesh, std::string const &texture)
  : AGameObject(pos, mesh, texture, (state == Destructible) ? OTHER : BLOCK), _state(state)
{
    (*this)->setScale(irr::core::vector3df(0.8f, 0.8f, 0.8f));
}

Wall::~Wall()
{
  
}

void                        Wall::dead()
{
  int			i;

  i = 2;//rand() % 8;
  switch (i)
    {
    case 0:
      new BonusSpeed(this->getMapPos());
      break;
    case 1:
      new BonusPower(this->getMapPos());
      break;
    case 2:
      new BonusFireBomb(this->getMapPos());
      break;      
    case 3:
      new ItemThrow(this->getMapPos());
      break;
    case 4:
      new BonusBombPass(this->getMapPos());
      break;
    case 5:
      new BonusBiggestMan(this->getMapPos());
      break;
    case 6:
      new BonusSmallestMan(this->getMapPos());
      break;
    case 7:
      new BonusInvincible(this->getMapPos());
      break;
    default:
      break;
    }
}

bool				Wall::isDestructible() const
{
  return ((_state == Destructible));
}

Wall::State			Wall::getState() const
{
  return (_state);
}
