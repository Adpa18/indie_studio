//
// Bomb.hpp for BOMB in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Thu Apr 28 16:19:48 2016 Victor Gouet
// Last update Wed May 11 16:34:01 2016 Victor Gouet
//

#ifndef ABOMB_HPP_
# define ABOMB_HPP_

# include "AGameObject.hpp"

class	ABomb	: public AGameObject
{

public:
  ABomb(std::string const &mesh, std::string const &texture);
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

protected:
  virtual void		disable();

public:
  virtual void                        dead();
  virtual bool				isDestructible() const;

public:
  virtual void		        willExplose() = 0;

private:
  void			run();

private:
  std::string   	mesh;
  std::string 		texture;

private:
  mutable bool			__active;

protected:
  int				_power;
  bool				use;
};

#endif
