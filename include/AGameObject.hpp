//
// AGameObject.hpp for AGAMEOBJECT in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Tue Apr 26 20:53:17 2016 Victor Gouet
// Last update Mon May 23 17:59:10 2016 Victor Gouet
//

#ifndef AGAMEOBJECT_HPP_
# define AGAMEOBJECT_HPP_

# include <time.h>
# include <string>
# include "IrrlichtController.hpp"
# include "ISerialize.hpp"

class	AGameObject	:	public ISerialize
{
public:
    enum Type {
        NONE = 0,
        CHARACTER = 1 << 0,
        BOMB = 1 << 1,
        ITEM = 1 << 2,
        BLOCK = 1 << 3,
				BONUS = 1 << 4,
				BOOM = 1 << 5,
        OTHER = 1 << 6
    };
public:
  AGameObject(irr::core::vector2df const &pos, std::string const &mesh,
              std::string const &texture, Type type = NONE, double timeout = -1);
  virtual ~AGameObject();

public:
  irr::scene::IAnimatedMeshSceneNode    *getSceneNode();
  irr::scene::IAnimatedMeshSceneNode    *operator->();
  AGameObject::Type                   getType() const;
  void                                setPos(irr::core::vector2df const &pos);
  irr::core::vector2df               getMapPos() const;
  irr::core::vector2df                getRealPos() const;
  void					setTimeOut(double timeout);
  void					setTimeOutWithoutInContainer(double timeout);
  void					addAnimation();
  void					removeAnnimation();
  int						getID() const;
  double				getTimeOutObj() const;
  bool					isObjectTimeOut() const;
  void					setType(Type);
  std::string			const	&getTexture() const;
  std::string			const	&getMesh() const;

public:
  virtual void                        dead() = 0;
  virtual bool			      isDestructible() const = 0;
  virtual void			      updateTimeOut();

public:
  bool					isTimeOut() const;
  irr::scene::ISceneNodeAnimator	*getAnimator() const;
  void					wait();

private:
  std::string				_texture;
  std::string				_mesh;

private:
  irr::scene::IAnimatedMeshSceneNode	*_node;
  irr::scene::ISceneNodeAnimator	*anime;
  Type                                  _type;

private:
  double				_timeout;
  double				_timer;
  double				_rltimeout;
};

#endif
