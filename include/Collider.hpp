//
// Created by wery_a on 06/05/16.
//

#ifndef CPP_INDIE_STUDIO_COLLIDER_HPP
# define CPP_INDIE_STUDIO_COLLIDER_HPP

# include <stack>
# include "BomberMap.hpp"

class Collider
{
public:
    Collider();
    virtual ~Collider();

public:
    std::vector<AGameObject*>   collid(irr::core::vector2df const &pos) const;
};

#endif //CPP_INDIE_STUDIO_COLLIDER_HPP