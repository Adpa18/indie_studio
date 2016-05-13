//
// Bomb.hpp for BOMB in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Thu Apr 28 16:19:48 2016 Victor Gouet
// Last update Fri May 13 11:18:43 2016 Victor Gouet
//

#ifndef ABOMB_HPP_
# define ABOMB_HPP_

# include "AGameObject.hpp"

class	ABomb	: public AGameObject
{

public:
  ABomb(std::string const &mesh, std::string const &texture, double timeout = 3);
  ABomb(ABomb const *);
  ABomb	&operator=(ABomb const *);
  virtual ~ABomb();

public:
  bool			isUse() const;

public:
  int			getPower() const;

public:
  void			operator<<(irr::core::vector2df const &pos);
  void		        setPower(int power);
  void			setVelocity(irr::core::vector2df const &);

private:
  virtual void		disable();

public:
  virtual void          dead();
  virtual bool		isDestructible() const;
  virtual void		updateTimeOut();

public:
  virtual void		willExplose() = 0;

private:
  void			run();

private:
  std::string   	mesh;
  std::string 		texture;

private:
  bool			_arrived;
  irr::core::vector2df	dir;
  irr::f32		frameDeltaTime;
  irr::f32		then;

private:
  mutable bool		__active;

protected:
  int			_power;
  bool			use;
  double		timeout;
};

#endif
