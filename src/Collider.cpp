/*
** Collider.cpp for cpp_indie_studio
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Apr 27 18:29:31 2016 Adrien WERY
** Last update	Wed Apr 27 21:22:08 2016 Adrien WERY
*/

#include "../include/Collider.hpp"

Collider::Collider(int flags) : _distance(13)
{
    this->_collMan = IrrlichtController::getSceneCollisionManager();
}

Collider::~Collider()
{

}

#include <iostream>

int     Collider::collid(irr::core::vector3df pos, Collider::Direction dir)
{
    // TODO Chaner distance if != dir
    irr::scene::ISceneNode              *selectedSceneNode;

    if (dir & Direction::RIGHT && (selectedSceneNode = this->hit(irr::core::line3d<irr::f32>(pos, pos + irr::core::vector3df(1, 0, 0) * this->_distance)))) {
        this->_ids.push_back(selectedSceneNode->getID());
        return (selectedSceneNode->getID());
    }
    if (dir & Direction::LEFT && (selectedSceneNode = this->hit(irr::core::line3d<irr::f32>(pos, pos + irr::core::vector3df(-1, 0, 0) * this->_distance)))) {
        this->_ids.push_back(selectedSceneNode->getID());
        return (selectedSceneNode->getID());
    }
    if (dir & Direction::UP && (selectedSceneNode = this->hit(irr::core::line3d<irr::f32>(pos, pos + irr::core::vector3df(0, 0, 1) * this->_distance)))) {
        this->_ids.push_back(selectedSceneNode->getID());
        return (selectedSceneNode->getID());
    }
    if (dir & Direction::DOWN && (selectedSceneNode = this->hit(irr::core::line3d<irr::f32>(pos, pos + irr::core::vector3df(0, 0, -1) * this->_distance)))) {
        this->_ids.push_back(selectedSceneNode->getID());
        return (selectedSceneNode->getID());
    }
    this->_ids.clear();
    return (-1);
}

irr::scene::ISceneNode  *Collider::hit(irr::core::line3d<irr::f32> ray) const
{
    irr::core::triangle3df              hitTriangle;
    irr::core::vector3df                intersection;

    return (this->_collMan->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, this->_flags, 0));
}

void                    Collider::setDistance(unsigned int distance)
{
    this->_distance = distance;
}

unsigned int            Collider::getDistance() const
{
    return (this->_distance);
}
