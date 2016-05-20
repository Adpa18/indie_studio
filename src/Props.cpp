//
// Created by consta_n on 19/05/16.
//

#include "../include/Props.hpp"

Props::Props(const std::string &mesh,
      const std::string &texture, irr::core::vector2df const &scale, int transparent)
    : AGameObject(irr::core::vector2df(0, 0), mesh, texture, OTHER) {
   (*this)->setPosition(irr::core::vector3df(0, 0, 0));
   if (scale.X && scale.Y)
      (*this)->getMaterial(0).getTextureMatrix(0).setTextureScale(scale.X,scale.Y);
   if (transparent)
      (*this)->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
}

void Props::dead() {

}

bool Props::isDestructible() const {
   return false;
}
