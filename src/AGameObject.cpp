//
// AGameObject.cpp for GAME OBJECT in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Tue Apr 26 21:00:41 2016 Victor Gouet
// Last update Tue May 10 19:12:09 2016 Victor Gouet
//

#include "../include/AGameObject.hpp"
#include "../include/BomberMap.hpp"
#include "../include/GameObjectTimeContainer.hpp"

AGameObject::AGameObject(irr::core::vector2df const &pos, std::string const &mesh, std::string const &texture, Type type, int timeout) : _type(type)
{
    BomberMap::getMap()->add(this, pos);
    irr::scene::IAnimatedMesh *meshNode = IrrlichtController::getSceneManager()->getMesh(mesh.c_str());

  time_t	timer;
  struct tm	y2k;

  this->_timeout = timeout;
  timer = time(NULL);

    if (timeout != -1)
      {
	y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
	y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;
	y2k.tm_gmtoff = 0; y2k.tm_isdst = 0; y2k.tm_wday = 0;
	y2k.tm_zone = 0;
	_timer = difftime(timer, mktime(&y2k));
	// A Mettre dans une list de GameObject qui vont disparaitre au bon d un moment
	
	GameObjectTimeContainer::SharedInstance()->add(this);

      }
    else
      {
	_timer = 0;
      }

  if (!meshNode)
    {
      IrrlichtController::getDevice()->drop();
      throw std::runtime_error("Failed to create IAnimatedMesh in AGameObject");
    }
  if ((_node = IrrlichtController::getSceneManager()->addAnimatedMeshSceneNode(meshNode, 0, 0)))
    {
        this->setPos(pos);
      _node->setMaterialTexture(0, IrrlichtController::getDriver()->getTexture(texture.c_str()));
      _node->setMD2Animation(irr::scene::EMAT_STAND);
      _node->setMaterialFlag(irr::video::EMF_LIGHTING,true);
    }
}

AGameObject::~AGameObject()
{
  if (_timeout != -1)
    GameObjectTimeContainer::SharedInstance()->remove(this);
  BomberMap::getMap()->remove(this);
  (*this)->remove();

    // this->dead();
    //  (*this)->remove();
    // this->_node->removeAll();
    // this->_node->remove();
}

bool				AGameObject::isTimeOut() const
{
  time_t	timer;
  struct tm	y2k;
  double	seconds;

  y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
  y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;
  y2k.tm_gmtoff = 0; y2k.tm_isdst = 0; y2k.tm_wday = 0;
  y2k.tm_zone = 0;

  timer = time(NULL);

  seconds = difftime(timer, mktime(&y2k));
  return (seconds >= (_timer + _timeout));
}

void			AGameObject::onTimeOut()
{
  // Remove From the list of timer object
}

irr::scene::IAnimatedMeshSceneNode *AGameObject::operator->()
{
  return (_node);
}

AGameObject::Type   AGameObject::getType() const
{
    return (this->_type);
}

void                AGameObject::setPos(irr::core::vector2df const &pos)
{
    BomberMap::getMap()->move(this, pos);
    _node->setPosition(irr::core::vector3df(pos.X - BomberMap::size_side / 2, 0, pos.Y - BomberMap::size_side / 2) * BomberMap::scale);
}

irr::core::vector2df    AGameObject::getMapPos() const
{
    return (BomberMap::getMap()->get(const_cast<AGameObject*>(this)));
}

irr::core::vector2df    AGameObject::getRealPos() const
{
    irr::core::vector3df    pos3df = _node->getPosition() / BomberMap::scale;

    return (irr::core::vector2df(pos3df.X + BomberMap::size_side / 2, pos3df.Z + BomberMap::size_side / 2));
}

// void                AGameObject::dead()
// {
//     BomberMap::getMap()->remove(this);
//     (*this)->remove();
// }
