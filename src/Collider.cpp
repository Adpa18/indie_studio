//
// Created by wery_a on 06/05/16.
//

#include "Collider.hpp"

Collider::Collider()
{

}

Collider::~Collider()
{

}

std::vector<AGameObject*>   Collider::collid(irr::core::vector2df const &pos) const
{
    return (BomberMap::getMap()->getObjsFromVector2(pos));
}