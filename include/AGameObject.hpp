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

class	AGameObject
{
public:
    enum Type {
        NONE = 0,
        CHARACTER = 1 << 0,
        BOMB = 1 << 1,
        ITEM = 1 << 2,
        BLOCK = 1 << 3,
        OTHER = 1 << 4
    };
public:
  AGameObject(irr::core::vector2di const &pos, std::string const &mesh,
              std::string const &texture, Type type = NONE);
  virtual ~AGameObject();

public:
  irr::scene::IAnimatedMeshSceneNode    *operator->();
    AGameObject::Type                   getType() const;
    void                                setPos(irr::core::vector2di const &pos);
    irr::core::vector2di                getPos() const;
    virtual void                        dead();
private:
  irr::scene::IAnimatedMeshSceneNode	*_node;
  Type                                  _type;
};

#endif
