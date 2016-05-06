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
# include "ACharacter.hpp"
# include "Wall.hpp"

class	BomberMap
{
public:
    static const int	size_side = 11;
    static const size_t	scale = 25;
public:
  BomberMap(std::string const &);
  BomberMap();

public:
    void  serialize(std::string const &) const;
    void  deserialize(std::string const &);

public:
    static BomberMap    *getMap();
    void    genMap();

private:
  void			generateMap();
  void		        generateGround();

public:
    void  add(AGameObject* obj, const irr::core::vector2df &pos);
    void  remove(AGameObject *obj);
    void  move(AGameObject *obj, const irr::core::vector2df &pos);
    std::vector<AGameObject *>  getObjsFromVector2(const irr::core::vector2df &pos) const;
    const irr::core::vector2df  get(AGameObject *obj);

private:
    std::map<AGameObject*, irr::core::vector2df> _objects;

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
    static BomberMap    *bomberMap;
};

#endif
