//
// Wall.cpp for WALL in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Apr 27 18:19:48 2016 Victor Gouet
// Last update Tue May 10 14:47:43 2016 Victor Gouet
//

#include "../include/Wall.hpp"
#include "../include/Texture.hpp"

Wall::Wall(irr::core::vector2df const &pos, State state) // 1 caisseMetal
  : AGameObject(pos, state == Invicible ? BomberManTexture::caisseIndestructibleMetalMD : BomberManTexture::caisseDestructibleMD,
		state == Invicible ? BomberManTexture::caisseIndestructibleTexture : BomberManTexture::caisseDestructibleTexture,
                (state == Destructible) ? OTHER : BLOCK), _state(state)
{
  
}

Wall::~Wall()
{
  
}

void                        Wall::dead()
{
  int			i;

  i = rand() % 6;
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
    default:
      break;
    }
  // std::cout << "JESUS CHRIST" << std::endl;
}

bool				Wall::isDestructible() const
{
  return ((_state == Destructible));
}

Wall::State			Wall::getState() const
{
  return (_state);
}
