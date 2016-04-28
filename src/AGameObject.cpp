//
// AGameObject.cpp for GAME OBJECT in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Tue Apr 26 21:00:41 2016 Victor Gouet
// Last update Thu Apr 28 11:30:09 2016 Victor Gouet
//

#include "../include/AGameObject.hpp"
#include <stdexcept>

AGameObject::AGameObject(irr::core::vector3df const &pos, std::string const &mesh, Collider *collider) : _collider(collider)
{
    static int i = 0;
  std::string		const strMd2(mesh + ".md2");
  std::string		const strBMP(mesh + ".png");

  irr::scene::IAnimatedMesh *meshNode =
    IrrlichtController::getSceneManager()->getMesh(strMd2.c_str());

  if (!meshNode)
    {
      IrrlichtController::getDevice()->drop();
      throw std::runtime_error("Failed to create IAnimatedMesh in AGameObject");
    }
  _node = IrrlichtController::getSceneManager()->addAnimatedMeshSceneNode(meshNode, 0, ++i);
  if (_node)
    {
      _node->setPosition(pos);
      _node->setMaterialTexture(0, IrrlichtController::getDriver()->getTexture(strBMP.c_str()));
      _node->setMD2Animation(irr::scene::EMAT_STAND);
      _node->setMaterialFlag(irr::video::EMF_LIGHTING,true);
      // _node->setScale(irr::core::vector3df(1.5, 1.5, 1.5));
      irr::scene::ITriangleSelector* selector = IrrlichtController::getSceneManager()->createTriangleSelector(_node);
      _node->setTriangleSelector(selector);
      selector->drop();
    }
}

AGameObject::~AGameObject()
{
    delete this->_collider;
    // this->_node->removeAll();
    // this->_node->remove();
}

irr::scene::IAnimatedMeshSceneNode *AGameObject::operator->()
{
  return (_node);
}

void        AGameObject::addCollider(Collider *collider)
{
    this->_collider = collider;
}

int     AGameObject::collid(irr::core::vector3df pos,IrrlichtController::Direction dir) const
{
    return (this->_collider->collid(pos, dir));
}
