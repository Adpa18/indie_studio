//
// BombContainer.cpp for BOMB in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Fri Apr 29 14:21:28 2016 Victor Gouet
// Last update Wed May 11 16:15:38 2016 Victor Gouet
//

#include "../include/BombContainer.hpp"

BombContainer::BombContainer()
{
}

BombContainer::~BombContainer()
{
  deleteAllBomb();
}

ABomb				*BombContainer::getBomb() const
{
  for (std::vector<ABomb *>::const_iterator	it = _bombs.begin(),
  	 end = _bombs.end() ; it != end ; ++it)
    {
      if (!(*it)->isUse())
  	return (*it);
    }
  return (NULL);
}

size_t			BombContainer::getBombsNbr() const
{
  return (_bombs.size());
}

std::vector<ABomb *>	const	&	BombContainer::getBombs() const
{
  return _bombs;
}

void				BombContainer::addBomb(ABomb *bomb)
{
  if (_bombs.size() < 9)
    _bombs.push_back(bomb);
}

void				BombContainer::upgradePowerBombs()
{
  for (std::vector<ABomb *>::iterator it = _bombs.begin(), end = _bombs.end() ; it != end ; ++it)
    {
      (*it)->setPower((*it)->getPower() + 1);
    }
}

// void				BombContainer::bombExplose()
// {
//   std::vector<ABomb *>::iterator	it;

//   it = _bombs.begin();
//   while (it != _bombs.end())
//     {
//       if ((*it)->isActive())
// 	(*it)->willExplose();
//       ++it;
//     }
// }

void				BombContainer::deleteAllBomb()
{
  _bombs.clear();
}
