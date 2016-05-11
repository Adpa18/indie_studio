//
// AGameObject.hpp for AGAMEOBJECT in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Tue Apr 26 20:53:17 2016 Victor Gouet
// Last update Wed May 11 15:45:12 2016 Victor Gouet
//

#ifndef AGAMEOBJECT_HPP_
# define AGAMEOBJECT_HPP_

# include <time.h>
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
        OTHER = 1 << 4,
	BONUS = 1 << 5
    };
public:
  AGameObject(irr::core::vector2df const &pos, std::string const &mesh,
              std::string const &texture, Type type = NONE, double timeout = -1);
  virtual ~AGameObject();

public:
  irr::scene::IAnimatedMeshSceneNode    *operator->();
    AGameObject::Type                   getType() const;
    void                                setPos(irr::core::vector2df const &pos);
    irr::core::vector2df                getMapPos() const;
    irr::core::vector2df                getRealPos() const;
  void					setTimeOut(double timeout);

public:
  virtual void                        dead() = 0;
  virtual bool				isDestructible() const = 0;

public:
  bool				isTimeOut() const;
  virtual void			onTimeOut();

private:
  irr::scene::IAnimatedMeshSceneNode	*_node;
  Type                                  _type;

private:
  int					_timeout;
  double				_timer;
};

#endif
