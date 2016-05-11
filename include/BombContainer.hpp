//
// BombContainer.hpp for BOMB in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Fri Apr 29 14:14:03 2016 Victor Gouet
// Last update Wed May 11 16:15:54 2016 Victor Gouet
//

#ifndef BOMBCONTAINER_HPP_
# define BOMBCONTAINER_HPP_

# include "ABomb.hpp"
# include <vector>

class	BombContainer
{
public:
  BombContainer();
  ~BombContainer();

public:
  ABomb				*getBomb() const;
  std::vector<ABomb *>	const	&getBombs() const;
  size_t			getBombsNbr() const;

public:
  void				addBomb(ABomb *);
  void				deleteAllBomb();
  // void				bombExplose();
  void			        upgradePowerBombs();

private:
  std::vector<ABomb *>		_bombs;
};

#endif
