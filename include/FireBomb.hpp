//
// FireBomb.hpp for FIRE in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Fri Apr 29 13:37:22 2016 Victor Gouet
// Last update Wed May 11 15:54:06 2016 Victor Gouet
//

#ifndef FIREBOMB_HPP_
# define FIREBOMB_HPP_

# include "ABomb.hpp"

class		FireBomb	: public ABomb
{
public:
  FireBomb();
  FireBomb	&operator=(ABomb const *);
  FireBomb(ABomb const *);
  virtual ~FireBomb();

public:
  virtual void	willExplose();
};

#endif
