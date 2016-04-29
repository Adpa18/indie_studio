//
// Bomb.hpp for BOMB in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Thu Apr 28 16:19:48 2016 Victor Gouet
// Last update Fri Apr 29 13:30:56 2016 Victor Gouet
//

#ifndef BOMB_HPP_
# define BOMB_HPP_

#include <condition_variable>
# include <mutex>
# include <thread>
# include "AGameObject.hpp"

class	Bomb	: public AGameObject
{

public:
  Bomb();
  Bomb(Bomb const &);
  Bomb	&operator=(Bomb const &);
  virtual ~Bomb();

public:
  bool			isAlive() const;
  bool			isUse() const;

public:
  void			operator<<(irr::core::vector3df const &);

private:
  virtual void		        willExplose();

private:
  void			run();

private:
  std::thread			*threadBomb;
  std::condition_variable	condVar;
  std::mutex			_mutex;

private:
  int				_power;

private:
  bool				alive;
  bool				use;
};

#endif
