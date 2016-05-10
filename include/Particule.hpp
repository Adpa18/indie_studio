//
// Created by wery_a on 10/05/16.
//

#ifndef PARTICULE_HPP
# define PARTICULE_HPP

# include "IrrlichtController.hpp"

class Particule
{
private:
    irr::scene::IParticleSystemSceneNode    *_particleSystem;
public:

    Particule(irr::core::vector3df const &pos, irr::core::vector3df const &dir, int power);
    virtual ~Particule();
};

#endif //PARTICULE_HPP
