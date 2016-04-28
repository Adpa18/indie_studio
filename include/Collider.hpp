/*
** Collider.hpp for cpp_indie_studio
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Apr 27 18:27:45 2016 Adrien WERY
** Last update	Wed Apr 27 21:03:53 2016 Adrien WERY
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
    enum Direction {
        LEFT = 1 << 0,
        RIGHT = 1 << 1,
        UP = 1 << 2,
        DOWN = 1 << 3
    };
private:
    unsigned int        _distance;
    int                 _flags;
    std::vector<int>    _ids;
    irr::scene::ISceneCollisionManager  *_collMan;
public:
    Collider (int flags = CHARACTER | BOMB | OTHER);
    virtual ~Collider ();
    int collid(irr::core::vector3df pos, Collider::Direction dir);
    irr::scene::ISceneNode  *hit(irr::core::line3d<irr::f32> ray) const;


    void                    setDistance(unsigned int distance);
    unsigned int            getDistance() const;
};

#endif /* !COLLIDER_HPP */
