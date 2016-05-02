/*
** Collider.hpp for cpp_indie_studio
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Apr 27 18:27:45 2016 Adrien WERY
** Last update	Mon May 02 18:37:25 2016 Adrien WERY
*/

#ifndef COLLIDER_HPP
# define COLLIDER_HPP

# include "IrrlichtController.hpp"
# include <vector>

class Collider {
public:
    enum Type {
        NONE = 0,
        CHARACTER = 1 << 0,
        BOMB = 1 << 1,
        OTHER = 1 << 2
    };
private:
    unsigned int        _distance;
    int                 _flags;
    std::vector<int>    _ids;
    irr::scene::ISceneCollisionManager  *_collMan;
public:
    Collider (int flags = CHARACTER | BOMB | OTHER);
    virtual ~Collider ();
    irr::scene::ISceneNode  *collid(irr::core::vector3df pos, IrrlichtController::Direction dir);
    irr::scene::ISceneNode  *hit(irr::core::line3d<irr::f32> ray) const;
    irr::scene::ISceneNode  *rangeHit(irr::core::vector3df pos, IrrlichtController::Direction dir) const;


    void                    setDistance(unsigned int distance);
    unsigned int            getDistance() const;
};

#endif /* !COLLIDER_HPP */
