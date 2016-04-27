/*
** Collider.hpp for cpp_indie_studio
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Apr 27 18:27:45 2016 Adrien WERY
** Last update	Wed Apr 27 19:47:40 2016 Adrien WERY
*/

#ifndef COLLIDER_HPP
# define COLLIDER_HPP

# include "IrrlichtController.hpp"
# include <vector>

class Collider {
private:
    unsigned int    distance;
public:
    Collider ();
    virtual ~Collider ();
    std::vector<irr::s32>   collid(irr::core::vector3df pos) const;
    void                    setDistance(unsigned int distance);
    unsigned int            getDistance() const;
public:
    enum Type {
        NONE = 0,
        CHARACTER = 1 << 0,
        BOMB = 1 << 1,
        OTHER = 1 << 2
    };
};

#endif /* !COLLIDER_HPP */
