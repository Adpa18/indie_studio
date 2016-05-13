//
// TrackerBomb.hpp for TRACKER in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Fri May 13 11:06:23 2016 Victor Gouet
// Last update Fri May 13 11:25:09 2016 Victor Gouet
//

#ifndef TRACKERBOMB_HPP_
# define TRACKERBOMB_HPP_

# include "ABomb.hpp"

class		TrackerBomb	: public ABomb
{
public:
  TrackerBomb();
  TrackerBomb	&operator=(ABomb const *);
  TrackerBomb(ABomb const *);
  virtual ~TrackerBomb();

public:
  virtual void	willExplose();
  virtual void	updateTimeOut();

// private:
//     bool        killObjects(irr::core::vector2df const &pos);
};

#endif
