/*
** Collider.cpp for cpp_indie_studio
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Apr 27 18:29:31 2016 Adrien WERY
** Last update	Wed Apr 27 20:01:58 2016 Adrien WERY
*/

#include "../include/Collider.hpp"

Collider::Collider()
{

}

Collider::~Collider()
{

}

std::vector<irr::s32>   Collider::collid(irr::core::vector3df pos) const
{
    irr::core::line3d<irr::f32>         ray;
    irr::core::triangle3df              hitTriangle;
    irr::core::vector3df                intersection;
    irr::scene::ISceneCollisionManager  *collMan = IrrlichtController::getSceneCollisionManager();

    ray.start = pos;
    ray.end = ray.start + irr::core::vector3df(1, 0, 0) * this->distance;
    ray.end = ray.start + irr::core::vector3df(-1, 0, 0) * this->distance;
    ray.end = ray.start + irr::core::vector3df(0, 0, 1) * this->distance;
    ray.end = ray.start + irr::core::vector3df(0, 0, -1) * this->distance;

    irr::scene::ISceneNode * selectedSceneNode = collMan->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, CHARACTER | BOMB | OTHER, 0);
}

void                    Collider::setDistance(unsigned int distance)
{
    this->distance = distance;
}

unsigned int            Collider::getDistance() const
{
    return (this->distance);
}
