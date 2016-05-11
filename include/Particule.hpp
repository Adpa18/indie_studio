//
// Created by wery_a on 10/05/16.
//

#ifndef PARTICULE_HPP
# define PARTICULE_HPP

# include "IrrlichtController.hpp"
# include "AGameObject.hpp"

class Particule : public  AGameObject
{
private:
    irr::scene::IParticleSystemSceneNode    *_particleSystem;
public:
    Particule(irr::core::vector3df const &pos, irr::core::vector3df const &dir, int power);
    virtual ~Particule();

public:
    virtual void                        dead();
    virtual bool				isDestructible() const;
};

#endif //PARTICULE_HPP
