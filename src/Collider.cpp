/*
** Collider.cpp for cpp_indie_studio
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Apr 27 18:29:31 2016 Adrien WERY
** Last update	Thu Apr 28 16:06:18 2016 Adrien WERY
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

int     Collider::collid(irr::core::vector3df pos, IrrlichtController::Direction dir)
{
    // TODO Chaner distance if != dir
    irr::scene::ISceneNode              *selectedSceneNode;

    if (dir & IrrlichtController::RIGHT && (selectedSceneNode = this->rangeHit(pos, dir))) {
        this->_ids.push_back(selectedSceneNode->getID());
        return (selectedSceneNode->getID());
    }
    if (dir & IrrlichtController::LEFT && (selectedSceneNode = this->rangeHit(pos, dir))) {
        this->_ids.push_back(selectedSceneNode->getID());
        return (selectedSceneNode->getID());
    }
    if (dir & IrrlichtController::UP && (selectedSceneNode = this->rangeHit(pos, dir))) {
        this->_ids.push_back(selectedSceneNode->getID());
        return (selectedSceneNode->getID());
    }
    if (dir & IrrlichtController::DOWN && (selectedSceneNode = this->rangeHit(pos, dir))) {
        this->_ids.push_back(selectedSceneNode->getID());
        return (selectedSceneNode->getID());
    }
    this->_ids.clear();
    return (-1);
}

irr::scene::ISceneNode  *Collider::rangeHit(irr::core::vector3df pos, IrrlichtController::Direction dir) const
{
    irr::scene::ISceneNode      *selectedSceneNode = NULL;
    irr::core::line3d<irr::f32> ray;
    irr::core::vector3df        vec_dir;

    switch (dir) {
        case IrrlichtController::LEFT:
            vec_dir = irr::core::vector3df(-1, 0, 0);
            break;
        case IrrlichtController::RIGHT:
            vec_dir = irr::core::vector3df(1, 0, 0);
            break;
        case IrrlichtController::UP:
            vec_dir = irr::core::vector3df(0, 0, 1);
            break;
        case IrrlichtController::DOWN:
            vec_dir = irr::core::vector3df(0, 0, -1);
            break;
    }
    ray.start = pos;
    ray.end = pos + vec_dir * this->_distance;
    if ((selectedSceneNode = this->hit(irr::core::line3d<irr::f32>(pos, pos + vec_dir * this->_distance)))) {
        return (selectedSceneNode);
    }
    // pos += (vec_dir * IrrlichtController::scale / 2);
    // if ((selectedSceneNode = this->hit(irr::core::line3d<irr::f32>(pos, pos + vec_dir * this->_distance)))) {
    //     return (selectedSceneNode);
    // }
    // pos -= (vec_dir * IrrlichtController::scale / 2);
    // if ((selectedSceneNode = this->hit(irr::core::line3d<irr::f32>(pos, pos + vec_dir * this->_distance)))) {
    //     return (selectedSceneNode);
    // }
    return (NULL);
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
