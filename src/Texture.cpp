//
// Texture.cpp for TEXTURE in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Tue May 10 14:22:36 2016 Victor Gouet
// Last update Fri May 13 11:44:36 2016 Victor Gouet
//

#include <iostream>
#include "../include/Texture.hpp"

// STOP TOUCHER A SA MAIS TON PUTAIN DE BINAIRE A LA RACINE ET C'EST TOUT
const std::string BomberManTexture::path = "media/";


const std::map<std::string, struct model>  BomberManTexture::_models = {
        // BomberMap
        {"ground", {"", BomberManTexture::path + "grass.png"}},
        {"cubeIndestructible", {BomberManTexture::path + "cube_bottom.md2", BomberManTexture::path + "cubeDestrutible3.png"}},
        {"cubeDestructible", {BomberManTexture::path + "barrel.md2", BomberManTexture::path + "barrel.png"}},
        {"edge", {BomberManTexture::path + "cube_bottom.md2", BomberManTexture::path + "wall.png"}},
        // {"ground", {"", BomberManTexture::path + "grass.png"}},
        // {"cubeIndestructible", {BomberManTexture::path + "cube_bottom.md2", BomberManTexture::path + "cubeDestrutible3.png"}},
        // {"cubeDestructible", {BomberManTexture::path + "cube_bottom.md2", BomberManTexture::path + "cubeIndestructible3.png"}},
        // {"edge", {BomberManTexture::path + "column.md3", BomberManTexture::path + "column.png"}},
        // {"ground", {"", BomberManTexture::path + "grass.png"}},
        // {"cubeIndestructible", {BomberManTexture::path + "cube_bottom.md2", BomberManTexture::path + "cubeDestrutible3.png"}},
        // {"cubeDestructible", {BomberManTexture::path + "cube_bottom.md2", BomberManTexture::path + "cubeIndestructible3.png"}},
        // {"edge", {BomberManTexture::path + "cube_bottom.md2", BomberManTexture::path + "wall.png"}},
        // {"ground", {"", BomberManTexture::path + "grass.png"}},
        // {"cubeIndestructible", {BomberManTexture::path + "cube_bottom.md2", BomberManTexture::path + "cubeDestrutible3.png"}},
        // {"cubeDestructible", {BomberManTexture::path + "cube_bottom.md2", BomberManTexture::path + "cubeIndestructible3.png"}},
        // {"edge", {BomberManTexture::path + "cylinder_bottom.md2", BomberManTexture::path + "edge.png"}},
        // {"ground", {"", BomberManTexture::path + "grass.png"}},
        // {"cubeIndestructible", {BomberManTexture::path + "cube_bottom.md2", BomberManTexture::path + "wall.png"}},
        // {"cubeDestructible", {BomberManTexture::path + "barrel.md2", BomberManTexture::path + "barrel.png"}},
        // {"edge", {BomberManTexture::path + "column.md3", BomberManTexture::path + "column.png"}},
        // {"ground", {"", BomberManTexture::path + "grass.png"}},
        // {"cubeIndestructible", {BomberManTexture::path + "column.md3", BomberManTexture::path + "column.png"}},
        // {"cubeDestructible", {BomberManTexture::path + "barrel.md2", BomberManTexture::path + "barrel.png"}},
        // {"edge", {BomberManTexture::path + "cube_bottom.md2", BomberManTexture::path + "wall.png"}},
        // Players
        {"ziggs", {BomberManTexture::path + "ziggs_snow.md3", BomberManTexture::path + "ziggs_snow.png"}},
	// Bomb
        {"fireBomb", {BomberManTexture::path + "pokeball.md2", BomberManTexture::path + "pokeball.png"}},
	{"trackerBomb", {BomberManTexture::path + "pokeball.md2", BomberManTexture::path + "pokeball.png"}},
	// Explosion
        {"fireExplosion", {BomberManTexture::path + "cube.md2", BomberManTexture::path + "explosion.jpg"}},
        // Bonus
        {"bonusBombPass", {BomberManTexture::path + "pokeball.md2", BomberManTexture::path + "pokeball.png"}},
        {"bonusFireBomb", {BomberManTexture::path + "salameche.md2", BomberManTexture::path + "salameche.png"}},
        {"bonusPower", {BomberManTexture::path + "carapuce.md2", BomberManTexture::path + "carapuce.png"}},
        {"bonusSpeed", {BomberManTexture::path + "cube.md2", BomberManTexture::path + "cubeIndestructible.png"}},
        {"bonusBiggestMan", {BomberManTexture::path + "cube.md2", BomberManTexture::path + "cubeIndestructible.png"}},
        {"bonusSmallestMan", {BomberManTexture::path + "cube.md2", BomberManTexture::path + "cubeIndestructible.png"}},
	{"bonusInvincible", {BomberManTexture::path + "cube.md2", BomberManTexture::path + "cubeIndestructible.png"}},
        // Items
        {"itemThrow", {BomberManTexture::path + "bulbizarre.md2", BomberManTexture::path + "bulbizarre.png"}},
};

void BomberManTexture::loadTexture()
{
    for (std::map<std::string, struct model>::const_iterator it = _models.begin(); it != _models.end(); ++it) {
        if ((*it).second.mesh != "") {
            IrrlichtController::getSceneManager()->getMesh((*it).second.mesh.c_str());
        }
         if ((*it).second.texture != "") {
             IrrlichtController::getDriver()->getTexture((*it).second.texture.c_str());
         }
    }
}

const struct model &BomberManTexture::getModel(const std::string &model)
{
    return (_models.find(model)->second);
}
