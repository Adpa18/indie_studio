//
// ACharacter.hpp for ACHARACTER in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 09:36:14 2016 Victor Gouet
// Last update Wed Apr 27 09:52:17 2016 Victor Gouet
//

#ifndef ACHARACTER_HPP_
# define ACHARACTER_HPP_

# include "AGameObject.hpp"

class	ACharacter	: public AGameObject
{
private:
  const double BASICSPEED = 0.3;

public:
  ACharacter(std::string const &name, irr::core::vector3df const &pos, std::string const &mesh);
  virtual ~ACharacter();

public:
  std::string const &   getName() const;
  double                getMouveSpeed() const;
  void                  move(int x, int y, int z);
  void                  move(int x, int y);

private:
  std::string const	_name;
  // std::vector<Bomb>	bombs;
  // Bonus			*bonus;
  double		mouveSpeed;
};

#endif
