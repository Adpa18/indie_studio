//
// ABonus.cpp for BONUS in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Mon May  9 13:25:32 2016 Victor Gouet
// Last update Mon May  9 13:31:13 2016 Victor Gouet
//

#include "../include/ABonus.hpp"
#include "../include/BomberMap.hpp"

ABonus::ABonus(irr::core::vector2df const &pos, std::string const &mesh,
	       std::string const &texture, Type type)
  : AGameObject(pos, mesh, texture, type)
{
    (*this)->setPosition((*this)->getPosition() + irr::core::vector3df(0, BomberMap::scale / 2, 0));
//    (*this)->setRotation(irr::core::vector3df(45, 45, 45));
    (*this)->setScale(irr::core::vector3df(0.5f, 0.5f, 0.5f));
    irr::scene::ISceneNodeAnimator *anim =IrrlichtController::getSceneManager()->createRotationAnimator(irr::core::vector3df(0,1,0));
    (*this)->addAnimator(anim);
    anim->drop();
}

ABonus::~ABonus()
{
}
