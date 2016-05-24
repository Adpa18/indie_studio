//
// BomberMap.hpp for MAP in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 18:09:53 2016 Victor Gouet
// Last update Mon May 23 15:03:09 2016 Victor Gouet
//

#ifndef BOMBERMAP_HPP_
# define BOMBERMAP_HPP_

# include <vector>
# include <string>
# include "ACharacter.hpp"
# include "Wall.hpp"
# include "Props.hpp"
# include "Texture.hpp"

# define SMALL_SIZE 9
# define MEDIUM_SIZE 13
# define LARGE_SIZE 15

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
  ~BomberMap();

public:
  void  save() const;
  void  deserialize();
  void  genMap();
  std::vector<irr::core::vector2df> const	&getSpawn() const;

public:
  static BomberMap    *getMap();
  static void		newMap(Size mapSize);
  static void		newMap(std::string const &filename);
  static void		createMapFromSave(std::string const &filename);
  static void		deleteMap();
  static bool		isInstantiate();


private:
  void			generateMap();
  void		        generateGround();
  bool			canPutDestructibleWall(int x, int y) const;
  void			initSpawn();
  std::string		getCurrentDate() const;

public:
  void  add(AGameObject* obj, const irr::core::vector2df &pos);
  void  remove(AGameObject *obj);
  void  move(AGameObject *obj, const irr::core::vector2df &pos);
  int	getSize() const;
  std::map<AGameObject *, irr::core::vector2df>	const &getObjects() const;
  irr::scene::ICameraSceneNode *get_camera() const;
  void		refreshCamera();
  std::vector<AGameObject *>  getObjsFromVector2(const irr::core::vector2df &pos) const;
  const irr::core::vector2df  get(AGameObject *obj);
  std::vector<AGameObject *> const &getCharacters() const;
  void    loadModel(struct model mod);
  int getDangerAtPos(int x, int y) const;
  void setDangerAtPos(int x, int y, int value);
  int getDangerAtPos(const irr::core::vector2df &pos) const;
  void setDangerAtPos(const irr::core::vector2df &pos, int value);
  void displayDangerMap();

private:
  std::map<AGameObject*, irr::core::vector2df> _objects;
  std::vector<Props*> _props;
  std::vector<AGameObject *>			      _characters;
  std::vector<irr::core::vector2df>		_spawner;
  Size						_mapSize;
  const std::string                 _filename;
  irr::scene::ICameraSceneNode      *_camera;
  irr::core::vector3df              _target;
  irr::core::vector3df              _camera_pos;
  std::pair<std::string , std::string> _walls[3];
  int                                  **_danger_map;
private:
  static BomberMap    *bomberMap;
  irr::scene::ISceneNode    *_ground;

  /* TERRAIN */
  irr::scene::IAnimatedMesh	*terrain_model;
  /* LIGHT */
  std::vector<irr::scene::ILightSceneNode*>	lightVector;
};

#endif
