//
// TrackerBomb.cpp for TRACKER BOMB in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Fri May 13 11:04:11 2016 Victor Gouet
// Last update Sat May 14 17:14:49 2016 Victor Gouet
//

#include "../include/TrackerBomb.hpp"
#include "../include/BomberMap.hpp"
#include "../include/Texture.hpp"
#include "../include/Explosion.hpp"

TrackerBomb::TrackerBomb(int id)
  : ABomb(BomberManTexture::getModel("trackerBomb").mesh,
	  BomberManTexture::getModel("trackerBomb").texture, 5, id)
{
  targetID = -1;
  actual = getMapPos();
}

TrackerBomb::~TrackerBomb()
{
  dead();
}

TrackerBomb	&TrackerBomb::operator=(ABomb const *other)
{
  use = false;
  (*this)->setVisible(false);
  this->_power = other->getPower();
  return (*this);
}

TrackerBomb::TrackerBomb(ABomb const *other) : ABomb(other)
{
  *this = other;
}

#include <iostream>

void	TrackerBomb::updateTimeOut()
{
  AGameObject		*target = NULL;
  irr::core::vector2df	normal;
  irr::core::vector2df	direction;

  std::vector<AGameObject *>	const &charact = BomberMap::getMap()->getCharacters();

  for (std::vector<AGameObject *>::const_iterator it = charact.begin(), end = charact.end() ; it != end ; ++it)
    {
      if ((*(*it))->getID() != characterId && (targetID == (*(*it))->getID() || targetID == -1))
	{
	  targetID = (*it)->getID();
	  target = (*it);
	}
    }
  if (!target)
    return ;
  // GET LA TARGET MAIS SA BOUGE PAS HELP
}

void		TrackerBomb::willExplose()
{
  std::cout << "BOOM" << std::endl;
  targetID = -1;
}
