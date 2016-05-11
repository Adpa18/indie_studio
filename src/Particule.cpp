//
// Created by wery_a on 10/05/16.
//

#include "Particule.hpp"
#include "Texture.hpp"

Particule::Particule(irr::core::vector3df const &pos, irr::core::vector3df const &dir, int power)
    :AGameObject(irr::core::vector2df(pos.X, pos.Y), BomberManTexture::emptyMD, BomberManTexture::emptyTexture, AGameObject::NONE, 1)
{
    irr::scene::IParticleEmitter            *emitter;
    irr::scene::IParticleAffector           *affector;

    _particleSystem = IrrlichtController::getSceneManager()->addParticleSystemSceneNode(false);
    _particleSystem->setPosition(pos);
    emitter = _particleSystem->createBoxEmitter(
            irr::core::aabbox3d<irr::f32>(-10,0,-10,10,0,10), dir / 20, 10, 50,
            irr::video::SColor(0,255,255,255), irr::video::SColor(0,255,255,255),
            500, 500 * power, // duree de vie min / max
            0, // angle max d'ecart / direction prevue
            irr::core::dimension2df(40.0f,40.0f),
            irr::core::dimension2df(50.0f,50.0f)
    );
    _particleSystem->setEmitter(emitter);
    emitter->drop();
    _particleSystem->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _particleSystem->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
    _particleSystem->setMaterialTexture(0, IrrlichtController::getDriver()->getTexture(BomberManTexture::blueParticuleTexture.c_str()));
    _particleSystem->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
    affector = _particleSystem->createFadeOutParticleAffector(irr::video::SColor(0,0,0,0), 1200);
    _particleSystem->addAffector(affector);
    affector->drop();
}

Particule::~Particule()
{
    _particleSystem->setEmitter(0);
}

void        Particule::dead()
{

}

bool        Particule::isDestructible() const
{
    return (true);
}
