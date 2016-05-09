//
// Bomb.hpp for BOMB in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Thu Apr 28 16:19:48 2016 Victor Gouet
// Last update Mon May  9 15:25:56 2016 Victor Gouet
//

#ifndef ABOMB_HPP_
# define ABOMB_HPP_

# include <condition_variable>
# include <mutex>
# include <thread>
# include "AGameObject.hpp"

class	ABomb	: public AGameObject
{

public:
  ABomb();
  ABomb(ABomb const *);
  ABomb	&operator=(ABomb const *);
  virtual ~ABomb();

public:
  bool			isAlive() const;
  bool			isUse() const;
  bool			isActive() const;

private:
  bool		        isNotUse() const;

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

protected:
  void			newThreadBomb()
  {
    threadBomb = new std::thread([&] {run(); });
  }

private:
  std::thread			*threadBomb;
  std::condition_variable	condVar;
  mutable std::mutex			_mutex;
  mutable bool			__active;

protected:
  int				_power;
  bool				alive;
  bool				use;
};

#endif
