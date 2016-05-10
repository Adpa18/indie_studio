//
// Created by wery_a on 10/05/16.
//

#include "Particule.hpp"

Particule::Particule(irr::core::vector3df const &pos, irr::core::vector3df const &dir, int power)
{
    irr::scene::IParticleEmitter            *emitter;
    irr::scene::IParticleAffector           *affector;

    _particleSystem = IrrlichtController::getSceneManager()->addParticleSystemSceneNode(false);
    _particleSystem->setPosition(pos);
    emitter = _particleSystem->createBoxEmitter(
            irr::core::aabbox3d<irr::f32>(-10,0,-10,10,0,10), dir / 20, 10, 500,
            irr::video::SColor(0,255,255,255), irr::video::SColor(0,255,255,255),
            500, 500 * power, // duree de vie min / max
            0, // angle max d'ecart / direction prevue
            irr::core::dimension2df(8.0f,8.0f),
            irr::core::dimension2df(14.0f,14.0f)
    );
    _particleSystem->setEmitter(emitter);
    emitter->drop();
    _particleSystem->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _particleSystem->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
    _particleSystem->setMaterialTexture(0, IrrlichtController::getDriver()->getTexture("media/blueFire.jpg"));
    _particleSystem->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
    affector = _particleSystem->createFadeOutParticleAffector(irr::video::SColor(0,0,0,0), 1200);
    _particleSystem->addAffector(affector);
    affector->drop();
}

Particule::~Particule()
{
//    _particleSystem->setEmitter(0);
}