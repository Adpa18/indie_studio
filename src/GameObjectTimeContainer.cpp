//
// GameObjectTimeContainer.cpp for TIME in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Tue May 10 18:55:37 2016 Victor Gouet
// Last update Wed May 11 09:44:03 2016 Victor Gouet
//

#include <iostream>
#include "../include/GameObjectTimeContainer.hpp"

GameObjectTimeContainer	*GameObjectTimeContainer::instance = NULL;

GameObjectTimeContainer::GameObjectTimeContainer()
{

}

GameObjectTimeContainer::~GameObjectTimeContainer()
{

}

GameObjectTimeContainer *GameObjectTimeContainer::SharedInstance()
{
  if (instance == NULL)
    {
      instance = new GameObjectTimeContainer();
    }
  return (instance);
}

void				GameObjectTimeContainer::remove(AGameObject *obj)
{
  container.remove(obj);
}

void				GameObjectTimeContainer::add(AGameObject *obj)
{
  container.push_back(obj);
}

void				GameObjectTimeContainer::callTimeOutObjects()
{
  std::list<AGameObject *>::iterator	it = container.begin();

  while (it != container.end())
    {
      if ((*it)->isTimeOut())
	{
	  (*it)->dead();
	  if ((*it)->isDestructible())
	    delete (*it);
	  it = container.erase(it);
	  std::cout << "TIME OUT ! OBJ destroy" << std::endl;
	}
      else
	++it;
    }
}
