//
// Texture.cpp for TEXTURE in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Tue May 10 14:22:36 2016 Victor Gouet
// Last update Tue May 10 15:56:50 2016 Victor Gouet
//

#include "../include/Texture.hpp"
#include "../include/IrrlichtController.hpp"

const std::string BomberManTexture::path = "media/";

const std::string BomberManTexture::ziggsTexture = BomberManTexture::path + "ziggs.png";
const std::string BomberManTexture::ziggsMD = BomberManTexture::path + "ziggs.md3";

const std::string BomberManTexture::caisseDestructibleTexture = BomberManTexture::path + "caisse.png";
const std::string BomberManTexture::caisseDestructibleMD = BomberManTexture::path + "caisse.md2";

const std::string BomberManTexture::caisseIndestructibleTexture = BomberManTexture::path + "caisse-metal.png";
const std::string BomberManTexture::caisseIndestructibleMD = BomberManTexture::path + "caisse-metal.md2";

const std::string BomberManTexture::fireBombTexture = BomberManTexture::path + "pokeball.png";
const std::string BomberManTexture::fireBombMD = BomberManTexture::path + "pokeball.md2";

const std::string BomberManTexture::bonusFireBombTexture = BomberManTexture::path + "salameche.png";
const std::string BomberManTexture::bonusFireBombMD = BomberManTexture::path + "salameche.md2";

const std::string BomberManTexture::bonusPowerTexture = BomberManTexture::path + "carapuce.png";
const std::string BomberManTexture::bonusPowerMD = BomberManTexture::path + "carapuce.md2";

const std::string BomberManTexture::bonusSpeedTexture = BomberManTexture::path + "caisse-metal.png";
const std::string BomberManTexture::bonusSpeedMD = BomberManTexture::path + "caisse-metal.md2";

const std::string BomberManTexture::itemThrowTexture = BomberManTexture::path + "bulbizarre.png";
const std::string BomberManTexture::itemThrowMD = BomberManTexture::path + "bulbizarre.md2";

void BomberManTexture::loadTexture()
{
  IrrlichtController::getDriver()->getTexture(ziggsTexture.c_str());
  IrrlichtController::getDriver()->getTexture(caisseDestructibleTexture.c_str());
  IrrlichtController::getDriver()->getTexture(caisseIndestructibleTexture.c_str());
  IrrlichtController::getDriver()->getTexture(fireBombTexture.c_str());
  IrrlichtController::getDriver()->getTexture(bonusFireBombTexture.c_str());
  IrrlichtController::getDriver()->getTexture(bonusPowerTexture.c_str());
  IrrlichtController::getDriver()->getTexture(bonusSpeedTexture.c_str());
  IrrlichtController::getDriver()->getTexture(itemThrowTexture.c_str());

  IrrlichtController::getSceneManager()->getMesh(ziggsMD.c_str());
  IrrlichtController::getSceneManager()->getMesh(caisseDestructibleMD.c_str());
  IrrlichtController::getSceneManager()->getMesh(caisseIndestructibleMD.c_str());
  IrrlichtController::getSceneManager()->getMesh(fireBombMD.c_str());
  IrrlichtController::getSceneManager()->getMesh(bonusFireBombMD.c_str());
  IrrlichtController::getSceneManager()->getMesh(bonusPowerMD.c_str());
  IrrlichtController::getSceneManager()->getMesh(bonusSpeedMD.c_str());
  IrrlichtController::getSceneManager()->getMesh(itemThrowMD.c_str());
}
