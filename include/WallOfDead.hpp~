//
// WallOfDead.hpp for DEAD in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Jun  1 14:14:10 2016 Victor Gouet
// Last update Wed Jun  1 14:30:22 2016 Victor Gouet
//

#ifndef WALLOFDEAD_HPP_
# define WALLOFDEAD_HPP_

# include "AGameObject.hpp"
# include "Explosion.hpp"

class	WallOfDead	: public AGameObject
{
public:
  WallOfDead(irr::core::vector2df const &, int timeout);
  virtual ~WallOfDead();

public:
  static void		createWallOfDead(int size);

public:
  virtual void          dead();
  virtual bool		isDestructible() const;
  virtual void		updateTimeOut();
  virtual void	        serialize(irr::io::IXMLWriter *) const;

private:
  irr::core::vector2df	pos;
};

#endif
