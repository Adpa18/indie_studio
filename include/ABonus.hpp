//
// ABonus.hpp for BONUS in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Mon May  9 13:18:58 2016 Victor Gouet
// Last update Mon May  9 13:53:08 2016 Victor Gouet
//

#ifndef ABONUS_HPP_
# define ABONUS_HPP_

# include "ACharacter.hpp"

class		ABonus	: public AGameObject
{
public:
  ABonus(irr::core::vector2df const &, std::string const &mesh,
	 std::string const &texture, Type type = OTHER);
  virtual ~ABonus();

public:
  virtual void take(ACharacter &) = 0;
};

#endif
