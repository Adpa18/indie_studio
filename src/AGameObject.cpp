//
// AGameObject.cpp for GAME OBJECT in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Tue Apr 26 21:00:41 2016 Victor Gouet
// Last update Mon May  9 14:04:58 2016 Victor Gouet
//

#include "AGameObject.hpp"
#include "BomberMap.hpp"

AGameObject::AGameObject(irr::core::vector2df const &pos, std::string const &mesh, std::string const &texture, Type type) : _type(type)
{
    BomberMap::getMap()->add(this, pos);
    irr::scene::IAnimatedMesh *meshNode = IrrlichtController::getSceneManager()->getMesh(mesh.c_str());

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
    BomberMap::getMap()->remove(this);
    (*this)->remove();

    // this->dead();
    //  (*this)->remove();
    // this->_node->removeAll();
    // this->_node->remove();
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
