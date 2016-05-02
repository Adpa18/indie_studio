/*
** Collider.cpp for cpp_indie_studio
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Apr 27 18:29:31 2016 Adrien WERY
** Last update	Mon May 02 18:45:09 2016 Adrien WERY
*/

#include "../include/Collider.hpp"

Collider::Collider(int flags) : _distance(IrrlichtController::scale / 2)
{
    this->_collMan = IrrlichtController::getSceneCollisionManager();
}

Collider::~Collider()
{

}

#include <iostream>

irr::scene::ISceneNode  *Collider::collid(irr::core::vector3df pos, IrrlichtController::Direction dir)
{
    irr::scene::ISceneNode  *selectedSceneNode;

    if (dir & IrrlichtController::RIGHT && (selectedSceneNode = this->rangeHit(pos, dir))) {
        this->_ids.push_back(selectedSceneNode->getID());
        return (selectedSceneNode);
    }
    if (dir & IrrlichtController::LEFT && (selectedSceneNode = this->rangeHit(pos, dir))) {
        this->_ids.push_back(selectedSceneNode->getID());
        return (selectedSceneNode);
    }
    if (dir & IrrlichtController::UP && (selectedSceneNode = this->rangeHit(pos, dir))) {
        this->_ids.push_back(selectedSceneNode->getID());
        return (selectedSceneNode);
    }
    if (dir & IrrlichtController::DOWN && (selectedSceneNode = this->rangeHit(pos, dir))) {
        this->_ids.push_back(selectedSceneNode->getID());
        return (selectedSceneNode);
    }
    this->_ids.clear();
    return (NULL);
}

irr::scene::ISceneNode  *Collider::rangeHit(irr::core::vector3df pos, IrrlichtController::Direction dir) const
{
    irr::scene::ISceneNode      *selectedSceneNode = NULL;
    irr::core::vector3df        vec_dir;
    irr::core::vector3df        range_vec;

    switch (dir) {
        case IrrlichtController::LEFT:
            vec_dir = irr::core::vector3df(-1, 0, 0);
            range_vec = irr::core::vector3df(0, 0, 1);
            break;
        case IrrlichtController::RIGHT:
            vec_dir = irr::core::vector3df(1, 0, 0);
            range_vec = irr::core::vector3df(0, 0, 1);
            break;
        case IrrlichtController::UP:
            vec_dir = irr::core::vector3df(0, 0, 1);
            range_vec = irr::core::vector3df(1, 0, 0);
            break;
        case IrrlichtController::DOWN:
            vec_dir = irr::core::vector3df(0, 0, -1);
            range_vec = irr::core::vector3df(1, 0, 0);
            break;
    }
    // pos + vec_dir * IrrlichtController::scale / 2 //just for character
    if ((selectedSceneNode = this->hit(irr::core::line3d<irr::f32>(pos + vec_dir * IrrlichtController::scale / 2, pos + vec_dir * this->_distance)))) {
        return (selectedSceneNode);
    }
    pos += (range_vec * (IrrlichtController::scale / 2 - 1));
    if ((selectedSceneNode = this->hit(irr::core::line3d<irr::f32>(pos + vec_dir * IrrlichtController::scale / 2, pos + vec_dir * this->_distance)))) {
        return (selectedSceneNode);
    }
    pos -= (range_vec * (IrrlichtController::scale / 2 - 1));
    if ((selectedSceneNode = this->hit(irr::core::line3d<irr::f32>(pos + vec_dir * IrrlichtController::scale / 2, pos + vec_dir * this->_distance)))) {
        return (selectedSceneNode);
    }
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
