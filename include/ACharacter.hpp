//
// ACharacter.hpp for ACHARACTER in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 09:36:14 2016 Victor Gouet
// Last update Wed Apr 27 16:44:30 2016 Victor Gouet
//

#ifndef ACHARACTER_HPP_
# define ACHARACTER_HPP_

# include "AGameObject.hpp"

class	ACharacter	: public AGameObject
{
public:
    enum ACTION { IDLE = 0, LEFT, RIGHT, UP, DOWN, BOMB, ACT };

private:
    static constexpr double BASICSPEED = 10.0;

public:
  ACharacter(std::string const &name, irr::core::vector3df const &pos, std::string const &mesh);
  virtual ~ACharacter();

public:
  std::string const &   getName() const;
  double                getMouveSpeed() const;
  virtual void		compute() = 0;
  // void                  move(int x, int y, int z);
  // void                  move(int x, int y);

private:
  std::string const	_name;
  // std::vector<Bomb>	bombs;
  // Bonus			*bonus;
  double		mouveSpeed;

protected:
  irr::u32 then;

};

#endif
