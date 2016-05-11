//
// Texture.hpp for TEXTURE in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Tue May 10 14:24:03 2016 Victor Gouet
// Last update Wed May 11 11:07:05 2016 Victor Gouet
//

#ifndef TEXTURE_HPP_
# define TEXTURE_HPP_

# include <string>
# include "IrrlichtController.hpp"

class	BomberManTexture
{
public:
  static const std::string groundTexture;

  static const std::string blueParticuleTexture;

  static const std::string emptyTexture;
  static const std::string emptyMD;

  static const std::string ziggsTexture;
  static const std::string ziggsMD;
  
  static const std::string cubeDestructibleTexture;
  static const std::string cubeDestructibleMD;

    static const std::string cubeEdgeTexture;
  static const std::string cubeEdgeMD;

  static const std::string cubeIndestructibleTexture;
  static const std::string cubeIndestructibleMD;
  
  static const std::string fireBombTexture;
  static const std::string fireBombMD;
  
  static const std::string bonusFireBombTexture;
  static const std::string bonusFireBombMD;

  static const std::string bonusPowerTexture;
  static const std::string bonusPowerMD;

  static const std::string bonusSpeedTexture;
  static const std::string bonusSpeedMD;

  static const std::string itemThrowTexture;
  static const std::string itemThrowMD;

  static const std::string path;

public:
  static void loadTexture();

};

#endif
