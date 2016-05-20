//
// GameObjectTimeContainer.hpp for TIME in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Tue May 10 18:42:24 2016 Victor Gouet
// Last update Fri May 20 20:30:43 2016 Victor Gouet
//

#ifndef GAMEOBJECTTIMECONTAINER_HPP_
# define GAMEOBJECTTIMECONTAINER_HPP_

# include <list>
# include "AGameObject.hpp"

class	GameObjectTimeContainer
{
public:
  GameObjectTimeContainer();
  ~GameObjectTimeContainer();

public:
  static GameObjectTimeContainer *SharedInstance();

public:
  void				callTimeOutObjects();
  void				timerStop();
  void				add(AGameObject *);
  void			        remove(AGameObject *obj);

private:
  static GameObjectTimeContainer *instance;

private:
  std::list<AGameObject *>		container;
};

#endif
