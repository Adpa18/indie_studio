//
// Wall.hpp for WALL in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Apr 27 18:18:28 2016 Victor Gouet
// Last update Fri May  6 17:35:57 2016 Victor Gouet
//

#ifndef WALL_HPP_
# define WALL_HPP_

# include <string>
# include "AGameObject.hpp"

class	Wall : public AGameObject
{
public:
  enum 	State
    {
      Invicible,// = "media/caisseMetal",
      Destructible// = "media/caisse"
    };

public:
  Wall(irr::core::vector2df const &pos, State state = Destructible);
  virtual ~Wall();

public:
  virtual void                        dead();
  virtual bool				isDestructible() const;

public:
  State			getState() const;

private:
  State			_state;
};

#endif
