//
// BomberMap.hpp for MAP in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 18:09:53 2016 Victor Gouet
// Last update Sat May 14 22:55:27 2016 Victor Gouet
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
  static const int	size_side[3];// = {11, 16, 20};
    static const size_t	scale = 25;

public:
  enum	Size
    {
      SMALL,
      MEDIUM,
      LARGE
    };

public:
  BomberMap(std::string const &);
  BomberMap(Size mapSize = SMALL);
  virtual ~BomberMap();

public:
    void  serialize(std::string const &) const;
    void  deserialize(std::string const &);
  void    genMap();

public:
  static BomberMap    *getMap();
  static void		newMap(Size mapSize);
  static void		deleteMap();

private:
  void			generateMap();
  void		        generateGround();

public:
    void  add(AGameObject* obj, const irr::core::vector2df &pos);
    void  remove(AGameObject *obj);
    void  move(AGameObject *obj, const irr::core::vector2df &pos);
  int	getSize() const;

    std::vector<AGameObject *>  getObjsFromVector2(const irr::core::vector2df &pos) const;
    const irr::core::vector2df  get(AGameObject *obj);
  std::vector<AGameObject *> const &getCharacters() const;

private:
  std::map<AGameObject*, irr::core::vector2df> _objects;
  std::vector<AGameObject *>			_characters;
  Size						_mapSize;

private:
    char			_patron[11][11] = {
            {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E','E', 'E', 'E'},
            {'E', ' ', ' ', 'C', 'C', 'C', 'C', 'C',' ', ' ', 'E'},
            {'E', ' ', 'X', 'C', 'X', 'C', 'X', 'C','X', ' ', 'E'},
            {'E', 'C', 'C', 'C', 'C', 'C', 'C', 'C','C', 'C', 'E'},
            {'E', 'C', 'X', 'C', 'X', 'C', 'X', 'C','X', 'C', 'E'},
            {'E', 'C', 'C', 'C', 'C', 'C', 'C', 'C','C', 'C', 'E'},
            {'E', 'C', 'X', 'C', 'X', 'C', 'X', 'C','X', 'C', 'E'},
            {'E', 'C', 'C', 'C', 'C', 'C', 'C', 'C','C', 'C', 'E'},
            {'E', ' ', 'X', 'C', 'X', 'C', 'X', 'C','X', ' ', 'E'},
            {'E', ' ', ' ', 'C', 'C', 'C', 'C', 'C',' ', ' ', 'E'},
            {'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E','E', 'E', 'E'}
    };

private:
    static BomberMap    *bomberMap;
    irr::scene::ISceneNode    *_ground;
};

#endif
