//
// BomberMap.cpp for MAP in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Apr 27 18:14:09 2016 Victor Gouet
// Last update Wed Apr 27 18:38:46 2016 Victor Gouet
//

#include "../include/BomberMap.hpp"

BomberMap::BomberMap(std::string const &)
{
  
}

BomberMap::BomberMap(int width, int height)
{
  int		y;
  int		x;

  y = 0;
  while (y < height)
    {
      x = 0;
      while (x < width)
	{
	  _objects.push_back(new Wall(irr::core::vector3df(x, 0, y),
				      Wall::Destructible));
	  ++x;
	}
      ++y;
    }
}
