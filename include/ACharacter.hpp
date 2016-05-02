//
// ACharacter.hpp for ACHARACTER in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 09:36:14 2016 Victor Gouet
// Last update Sun May  1 18:43:56 2016 Victor Gouet
//

#ifndef ACHARACTER_HPP_
# define ACHARACTER_HPP_

# include "AGameObject.hpp"
# include "BombContainer.hpp"

class	ACharacter	: public AGameObject
{
public:
    enum ACTION { IDLE = 0, LEFT, RIGHT, UP, DOWN, BOMB, ACT };
    enum MD3_ANIMATION { STAY, RUN, ATTACK };

private:
    static constexpr double BASICSPEED = 10.0;

public:
  ACharacter(std::string const &name, irr::core::vector3df const &pos, std::string const &mesh, std::string const &texture);
  virtual ~ACharacter();

protected:
  void			setMD3Animation(MD3_ANIMATION anim);
  void			goLeft();
  void			goRight();
  void			goDown();
  void			goUp();

public:
  std::string const &   getName() const;
  double                getMoveSpeed() const;

public:
  void                setName(const std::string &);
  virtual void		compute() = 0;
  // void                  move(int x, int y, int z);
  // void                  move(int x, int y);

public:
  void			putBomb();

private:
  std::string	_name;
  BombContainer			*_bombContainer;
  // std::vector<Bomb *>	bombs;
  // Bonus			*bonus;
  double		moveSpeed;

protected:
  irr::u32 then;

};

#endif
