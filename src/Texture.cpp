//
// Texture.cpp for TEXTURE in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Tue May 10 14:22:36 2016 Victor Gouet
// Last update Fri May 20 15:36:27 2016 Victor Gouet
//

#include <iostream>
#include "../include/Texture.hpp"

// STOP TOUCHER A SA MAIS TON PUTAIN DE BINAIRE A LA RACINE ET C'EST TOUT
const std::string BomberManTexture::path = "media/_old/";
const std::string BomberManTexture::smallMap = "media/smallMap/";
const std::string BomberManTexture::mediumMap = "media/mediumMap/";
const std::string BomberManTexture::largeMap = "media/largeMap/";
const std::string BomberManTexture::bombs = "media/bombs/";
const std::string BomberManTexture::bonus = "media/bonus/";
const std::string BomberManTexture::characters = "media/characters/";
const std::string BomberManTexture::gui = "media/gui/";
const std::string BomberManTexture::other = "media/other/";


const std::map<std::string, struct model>  BomberManTexture::_models = {
        // smallMap
        // {"mapCurtain", {BomberManTexture::smallMap + "curtain.md3", BomberManTexture::smallMap + "Curtain01_D.BMP"}},
        // {"mapGoods", {BomberManTexture::smallMap + "goods.md3", BomberManTexture::smallMap + "Goods01_D.BMP"}},
        // {"mapGround", {BomberManTexture::smallMap + "ground.md3", BomberManTexture::smallMap + "Ground04_D.BMP"}},
        // {"mapPillar", {BomberManTexture::smallMap + "pillar.md3", BomberManTexture::smallMap + "Pillar01_D.BMP"}},
        // {"mapStatue", {BomberManTexture::smallMap + "statue.md3", BomberManTexture::smallMap + "Statue01_D.BMP"}},
        // {"mapTable", {BomberManTexture::smallMap + "table.md3", BomberManTexture::smallMap + "Table01_D.BMP"}},
        // {"mapTomb", {BomberManTexture::smallMap + "tomb.md3", BomberManTexture::smallMap + "Tomb01_D.BMP"}},
        // {"mapWall", {BomberManTexture::smallMap + "wall.md3", BomberManTexture::smallMap + "Wall01_D.BMP"}},

	{"carpet", {BomberManTexture::smallMap + "meshes/carpet.md3", BomberManTexture::smallMap + "textures/Carpet01_D.png"}},
	{"carpet5", {BomberManTexture::smallMap + "meshes/carpet5.md3", BomberManTexture::smallMap + "textures/Carpet03_D.png"}},
	{"chest3", {BomberManTexture::smallMap + "meshes/chest3.md3", BomberManTexture::smallMap + "textures/Chest03_D.BMP"}},
	{"chest4", {BomberManTexture::smallMap + "meshes/chest4.md3", BomberManTexture::smallMap + "textures/Chest04_D.BMP"}},
	{"curtain", {BomberManTexture::smallMap + "meshes/curtain.md3", BomberManTexture::smallMap + "textures/curtain_d.png"}},
	{"goods", {BomberManTexture::smallMap + "meshes/goods.md3", BomberManTexture::smallMap + "textures/goods_d.png"}},
	{"ground", {BomberManTexture::smallMap + "meshes/ground.md3", BomberManTexture::smallMap + "textures/ground_d1.png"}},
	{"light", {BomberManTexture::smallMap + "meshes/light.md3", BomberManTexture::smallMap + "textures/Light01_D.png"}},
	{"pillar", {BomberManTexture::smallMap + "meshes/pillar.md3", BomberManTexture::smallMap + "textures/pillar_d.png"}},
	{"statue", {BomberManTexture::smallMap + "meshes/statue.md3", BomberManTexture::smallMap + "textures/statue_d.png"}},
	{"table", {BomberManTexture::smallMap + "meshes/table.md3", BomberManTexture::smallMap + "textures/table_d.png"}},
	{"wall_left", {BomberManTexture::smallMap + "meshes/wall_left.md3", BomberManTexture::smallMap + "textures/wall_left.png"}},
	{"wall_right", {BomberManTexture::smallMap + "meshes/wall_right.md3", BomberManTexture::smallMap + "textures/wall_right.png"}},
	{"weapon", {BomberManTexture::smallMap + "meshes/weapon.md3", BomberManTexture::smallMap + "textures/weapon_d.png"}},




        // Characters
        {"ziggs", {BomberManTexture::characters + "ziggs.md3", BomberManTexture::characters + "ziggs.png"}},
        {"ziggsPool", {BomberManTexture::characters + "ziggs_pool.md3", BomberManTexture::characters + "ziggs_pool.png"}},
        {"ziggsSnow", {BomberManTexture::characters + "ziggs_snow.md3", BomberManTexture::characters + "ziggs_snow.png"}},
        {"ziggsGeneral", {BomberManTexture::characters + "ziggs_general.md3", BomberManTexture::characters + "ziggs_general.png"}},
        {"ziggsMad", {BomberManTexture::characters + "ziggs_mad.md3", BomberManTexture::characters + "ziggs_mad.png"}},
        // Bombes
        {"fireBomb", {BomberManTexture::bombs + "fireBomb.md2", BomberManTexture::bombs + "fireBomb.png"}},
        {"atomicBomb", {BomberManTexture::bombs + "atomicBomb.md2", BomberManTexture::bombs + "atomicBomb.png"}},
        {"trackerBomb", {BomberManTexture::bombs + "trackerBomb.md2", BomberManTexture::bombs + "trackerBomb.png"}},
        // Gui
        {"menuScene", {"", BomberManTexture::gui + "MenuScene.png"}},
        {"menuSceneStart", {"", BomberManTexture::gui + "MenuSceneStart.png"}},
        {"playerSelection", {"", BomberManTexture::gui + "PlayerSelection.png"}},
        {"playerButton", {"", BomberManTexture::gui + "PlayerButton.png"}},
        {"playerButtonIa", {"", BomberManTexture::gui + "PlayerButtonIaEasy.png"}},
        {"IAEasy", {"", BomberManTexture::gui + "PlayerButtonIaEasy.png"}},
        {"IAMedium", {"", BomberManTexture::gui + "PlayerButtonIaMedium.png"}},
        {"IAHard", {"", BomberManTexture::gui + "PlayerButtonIaHard.png"}},
        // Other
        {"fire", {"", BomberManTexture::other + "fire.jpg"}},
        {"fireAtomic", {"", BomberManTexture::other + "fireAtomic.jpg"}},
        {"fireExplosion", {BomberManTexture::path + "cube.md2", ""}},
        // Bonus
        {"bonusBombPass", {BomberManTexture::bonus + "bonusBombPass.md2", BomberManTexture::bonus + "bonusBombPass.png"}},
        {"bonusFireBomb", {BomberManTexture::bonus + "bonusFireBomb.md2", BomberManTexture::bonus + "bonusFireBomb.png"}},
        {"bonusPower", {BomberManTexture::bonus + "bonusPower.md2", BomberManTexture::bonus + "bonusPower.png"}},
        {"bonusSpeed", {BomberManTexture::bonus + "bonusSpeed.md2", BomberManTexture::bonus + "bonusSpeed.png"}},
        {"bonusBiggestMan", {BomberManTexture::bonus + "bonusBiggestMan.md2", BomberManTexture::bonus + "bonusBiggestMan.png"}},
        {"bonusSmallestMan", {BomberManTexture::bonus + "bonusSmallestMan.md3", BomberManTexture::bonus + "bonusSmallestMan.png"}},
        {"bonusInvincible", {BomberManTexture::bonus + "bonusInvincible.md2", BomberManTexture::bonus + "bonusInvincible.png"}},
        // Items
        {"itemThrow", {BomberManTexture::path + "bulbizarre.md2", BomberManTexture::path + "bulbizarre.png"}},

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
    const std::map<std::string, struct model>::const_iterator   it = _models.find(model);

    if (it == _models.end())
        throw std::runtime_error("Failed to load Model : " + model);
    return (it->second);
}
