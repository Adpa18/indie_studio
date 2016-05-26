//
// main.cpp for MAIN in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio/src
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Tue Apr 26 21:31:44 2016 Victor Gouet
// Last update Mon May  9 11:59:54 2016 Victor Gouet
//

#include "../include/GameManager.hpp"

int	main()
{
  GameManager::SharedInstance()->run();
  delete(GameManager::SharedInstance());
  return (0);
}
