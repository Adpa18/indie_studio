//
// Texture.cpp for TEXTURE in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Tue May 10 14:22:36 2016 Victor Gouet
// Last update Wed May 11 11:07:16 2016 Victor Gouet
//

#include "../include/Texture.hpp"
#include "../include/IrrlichtController.hpp"

//TODO : ifndef for path
const std::string BomberManTexture::path = "../media/";

//BomberMap
const std::string BomberManTexture::groundTexture = BomberManTexture::path + "grass.jpg";

const std::string BomberManTexture::cubeDestructibleTexture = BomberManTexture::path + "cubeDestrutible.png";
const std::string BomberManTexture::cubeDestructibleMD = BomberManTexture::path + "cube.md2";

const std::string BomberManTexture::cubeIndestructibleTexture = BomberManTexture::path + "cubeIndestructible.png";
const std::string BomberManTexture::cubeIndestructibleMD = BomberManTexture::path + "cube.md2";

const std::string BomberManTexture::cubeEdgeTexture = BomberManTexture::path + "cubeEdge.png";
const std::string BomberManTexture::cubeEdgeMD = BomberManTexture::path + "cube.md2";

// Players
const std::string BomberManTexture::ziggsTexture = BomberManTexture::path + "ziggs.png";
const std::string BomberManTexture::ziggsMD = BomberManTexture::path + "ziggs.md3";

const std::string BomberManTexture::emptyTexture = BomberManTexture::path + "empty.jpg";
const std::string BomberManTexture::emptyMD = BomberManTexture::path + "empty.md2";



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

const std::string BomberManTexture::blueParticuleTexture = BomberManTexture::path + "blueFire.jpg";

void BomberManTexture::loadTexture()
{
  IrrlichtController::getDriver()->getTexture(cubeDestructibleTexture.c_str());
  IrrlichtController::getDriver()->getTexture(cubeIndestructibleTexture.c_str());
  IrrlichtController::getDriver()->getTexture(emptyTexture.c_str());
  IrrlichtController::getDriver()->getTexture(ziggsTexture.c_str());
  IrrlichtController::getDriver()->getTexture(fireBombTexture.c_str());
  IrrlichtController::getDriver()->getTexture(bonusFireBombTexture.c_str());
  IrrlichtController::getDriver()->getTexture(bonusPowerTexture.c_str());
  IrrlichtController::getDriver()->getTexture(bonusSpeedTexture.c_str());
  IrrlichtController::getDriver()->getTexture(itemThrowTexture.c_str());
  IrrlichtController::getDriver()->getTexture(blueParticuleTexture.c_str());

  IrrlichtController::getSceneManager()->getMesh(cubeDestructibleMD.c_str());
  IrrlichtController::getSceneManager()->getMesh(cubeIndestructibleMD.c_str());
  IrrlichtController::getSceneManager()->getMesh(emptyMD.c_str());
  IrrlichtController::getSceneManager()->getMesh(ziggsMD.c_str());
  IrrlichtController::getSceneManager()->getMesh(fireBombMD.c_str());
  IrrlichtController::getSceneManager()->getMesh(bonusFireBombMD.c_str());
  IrrlichtController::getSceneManager()->getMesh(bonusPowerMD.c_str());
  IrrlichtController::getSceneManager()->getMesh(bonusSpeedMD.c_str());
  IrrlichtController::getSceneManager()->getMesh(itemThrowMD.c_str());
}
