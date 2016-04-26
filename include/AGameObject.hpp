//
// AGameObject.hpp for AGAMEOBJECT in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Tue Apr 26 20:53:17 2016 Victor Gouet
// Last update Tue Apr 26 21:17:15 2016 Victor Gouet
//

#ifndef AGAMEOBJECT_HPP_
# define AGAMEOBJECT_HPP_

# include <string>
# include "IrrlichtController.hpp"

class	AGameObject
{
public:
  AGameObject(irr::core::vector3df const &pos, std::string const &mesh);
  virtual ~AGameObject();

public:
  irr::scene::IAnimatedMeshSceneNode *operator->();

private:
  irr::scene::IAnimatedMeshSceneNode	*_node;
};

#endif
