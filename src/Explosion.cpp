//
// Created by wery_a on 11/05/16.
//

#include "Texture.hpp"
#include "Explosion.hpp"

Explosion::Explosion(irr::core::vector2df const &pos, std::string const &texture, double timeout)
        : AGameObject(pos, BomberManTexture::getModel("fireExplosion").mesh,
        BomberManTexture::getModel("fireExplosion").texture, Type::BOOM, timeout)
{
    (*this)->setVisible(false);
    _ps = IrrlichtController::getSceneManager()->addParticleSystemSceneNode(false);
    irr::scene::IParticleEmitter* em = _ps->createBoxEmitter(
    irr::core::aabbox3d<irr::f32>(-10,0,-10,10,1,10),
    irr::core::vector3df(0.0f,0.05f,0.0f), 80,100,
    irr::video::SColor(0,255,255,255), irr::video::SColor(0,255,255,255),
    800,2000,0,
    irr::core::dimension2df(10.f,10.f),
    irr::core::dimension2df(20.f,20.f));
    _ps->setEmitter(em);
    em->drop();
    irr::scene::IParticleAffector* paf = _ps->createFadeOutParticleAffector();
    _ps->addAffector(paf);
    paf->drop();
    _ps->setPosition((*this)->getPosition());
    _ps->setScale(irr::core::vector3df(1,1,1));
    _ps->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _ps->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
    _ps->setMaterialTexture(0, IrrlichtController::getDriver()->getTexture(texture.c_str()));
    _ps->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
}

Explosion::~Explosion()
{
  _ps->setEmitter(0);
}

void        Explosion::dead()
{
}

bool        Explosion::isDestructible() const
{
    return (true);
}
