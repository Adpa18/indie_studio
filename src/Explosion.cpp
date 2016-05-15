//
// Created by wery_a on 11/05/16.
//

#include "Texture.hpp"
#include "Explosion.hpp"

Explosion::Explosion(irr::core::vector2df const &pos, double timeout)
        : AGameObject(pos, BomberManTexture::getModel("fireExplosion").mesh,
        BomberManTexture::getModel("fireExplosion").texture, Type::BOOM, timeout)
{

}

Explosion::~Explosion()
{

}

void        Explosion::dead()
{

}

bool        Explosion::isDestructible() const
{
    return (true);
}