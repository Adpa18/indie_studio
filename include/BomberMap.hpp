//
// BomberMap.hpp for MAP in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Apr 27 18:09:53 2016 Victor Gouet
// Last update Wed Apr 27 19:39:26 2016 Victor Gouet
//

#ifndef BOMBERMAP_HPP_
# define BOMBERMAP_HPP_

# include <vector>
# include <string>
# include "Wall.hpp"

class	BomberMap
{
public:
  static const size_t	scale = 25;

public:
  BomberMap(std::string const &);
  BomberMap(int width, int height);

private:
  std::vector<AGameObject *>	_objects;
};

#endif
