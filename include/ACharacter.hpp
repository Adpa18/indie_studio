//
// ACharacter.hpp for ACHARACTER in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 09:36:14 2016 Victor Gouet
// Last update Mon May  9 21:50:08 2016 Victor Gouet
//

#ifndef ACHARACTER_HPP_
# define ACHARACTER_HPP_

# include <vector>
# include "AGameObject.hpp"
# include "BombContainer.hpp"
# include "AItem.hpp"

class	ACharacter	: public AGameObject
{
public:
    enum ACTION { IDLE = 0, LEFT, RIGHT, UP, DOWN, BOMB, ACT };
    enum MD3_ANIMATION { STAY, RUN, ATTACK };

private:
    static constexpr double BASICSPEED = 10.0;

public:
  ACharacter(std::string const &name, irr::core::vector2df const &pos,
             std::string const &mesh, std::string const &texture, int player);
  virtual ~ACharacter();

protected:
  void			setMD3Animation(MD3_ANIMATION anim);
    void        action(ACTION act);
    void        moveTo(irr::core::vector2df const &dir);

public:
  virtual void                  dead();
  virtual bool		        isDestructible() const;

public:
  void			setMoveSpeed(double);
    std::string const   &getName() const;
    double              getMoveSpeed() const;
    void		        putBomb();
    void                setName(const std::string &);
    void			    exploseHisBomb();
    void		        increasePowerBomb();

    virtual void		compute() = 0;

public:
  BombContainer		*getBombContainer() const;

private:
  std::string	                    _name;
    int                             _player;
  BombContainer			            *_bombContainer;
  double		                    moveSpeed;
    int					            anime;
    irr::core::vector2df            _last_act;
    bool                            _arrived;
    AItem					        *item;

protected:
  irr::u32 then;
  irr::f32  frameDeltaTime;

};

#endif
