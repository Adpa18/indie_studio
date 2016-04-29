//
// BomberMap.hpp for MAP in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 18:09:53 2016 Victor Gouet
// Last update Thu Apr 28 10:11:29 2016 Victor Gouet
//

#ifndef BOMBERMAP_HPP_
# define BOMBERMAP_HPP_

# include <vector>
# include <string>
# include "Wall.hpp"

class	BomberMap
{
public:
  BomberMap(std::string const &);
  BomberMap();

public:
    void  serialize(std::string const &) const;
    void  deserialize(std::string const &);

private:
  void			generateMap();
  void		        generateGround();

private:
  char			_patron[11][11] = {
    {'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X','X', 'X', 'X'},
    {'X', ' ', ' ', 'C', 'C', 'C', 'C', 'C',' ', ' ', 'X'},
    {'X', ' ', 'X', 'C', 'X', 'C', 'X', 'C','X', ' ', 'X'},
    {'X', 'C', 'C', 'C', 'C', 'C', 'C', 'C','C', 'C', 'X'},
    {'X', 'C', 'X', 'C', 'X', 'C', 'X', 'C','X', 'C', 'X'},
    {'X', 'C', 'C', 'C', 'C', 'C', 'C', 'C','C', 'C', 'X'},
    {'X', 'C', 'X', 'C', 'X', 'C', 'X', 'C','X', 'C', 'X'},
    {'X', 'C', 'C', 'C', 'C', 'C', 'C', 'C','C', 'C', 'X'},
    {'X', ' ', 'X', 'C', 'X', 'C', 'X', 'C','X', ' ', 'X'},
    {'X', ' ', ' ', 'C', 'C', 'C', 'C', 'C',' ', ' ', 'X'},
    {'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X','X', 'X', 'X'}
  };

private:
  std::vector<AGameObject *>	_objects;
};

#endif
