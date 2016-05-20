//
// Wall.hpp for WALL in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Apr 27 18:18:28 2016 Victor Gouet
// Last update Fri May 20 16:11:02 2016 Victor Gouet
//

#ifndef WALL_HPP_
# define WALL_HPP_

# include <map>
# include <string>
# include "AGameObject.hpp"
# include "BonusSpeed.hpp"
# include "BonusPower.hpp"
# include "BonusFireBomb.hpp"
# include "ItemThrow.hpp"
# include "BonusBombPass.hpp"
# include "BonusBiggestMan.hpp"
# include "BonusSmallestMan.hpp"
# include "BonusInvincible.hpp"

class	Wall : public AGameObject
{
public:
  enum 	State
    {
      Invicible,
      Destructible,
      Edge
    };

private:
  static const std::map<Wall::State, std::string> _types;
  // static const std::map<int, std::string> _wallSmallMap;
  

public:
  Wall(irr::core::vector2df const &pos, State state = Destructible);
  Wall(irr::core::vector2df const &pos, State state,
       std::string const &mesh, std::string const &texture);
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
