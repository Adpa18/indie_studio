//
// Created by wery_a on 11/05/16.
//

#ifndef CPP_INDIE_STUDIO_EXPLOSION_HPP
# define CPP_INDIE_STUDIO_EXPLOSION_HPP

# include "IrrlichtController.hpp"
# include "AGameObject.hpp"

class Explosion : public AGameObject {
public:
    Explosion(irr::core::vector2df const &pos, double timeout);
    virtual ~Explosion();

public:
    virtual void                        dead();
    virtual bool				isDestructible() const;
};

#endif //CPP_INDIE_STUDIO_EXPLOSION_HPP
