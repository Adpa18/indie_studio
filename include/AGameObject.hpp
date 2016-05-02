//
// AGameObject.hpp for AGAMEOBJECT in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Tue Apr 26 20:53:17 2016 Victor Gouet
// Last update Sat Apr 30 10:00:35 2016 Victor Gouet
//

#ifndef AGAMEOBJECT_HPP_
# define AGAMEOBJECT_HPP_

# include <string>
# include "IrrlichtController.hpp"
# include "Collider.hpp"

class	AGameObject
{
public:
  AGameObject(irr::core::vector3df const &pos, std::string const &mesh, std::string const &texture, Collider *collider = NULL);
  virtual ~AGameObject();

public:
  irr::scene::IAnimatedMeshSceneNode *operator->();
  void      addCollider(Collider *collider);
  irr::scene::ISceneNode    *collid(irr::core::vector3df pos, IrrlichtController::Direction dir) const;
  Collider  *getCollider() const;
private:
  irr::scene::IAnimatedMeshSceneNode	*_node;
  Collider                              *_collider;
};

#endif
