//
// BonusTrackerBomb.hpp for BONUS in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Sat May 21 12:33:01 2016 Victor Gouet
// Last update Sat May 21 12:33:26 2016 Victor Gouet
//

#ifndef BONUSTRACKERBOMB_HPP_
# define BONUSTRACKERBOMB_HPP_

# include "ABonus.hpp"

class		BonusTrackerBomb	: public ABonus
{
public:
  BonusTrackerBomb(irr::core::vector2df const &);
  virtual ~BonusTrackerBomb();

public:
  virtual void		take(ACharacter &);
  virtual void		dead();
  virtual bool		isDestructible() const;
};

#endif
