//
// Texture.hpp for TEXTURE in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Tue May 10 14:24:03 2016 Victor Gouet
// Last update Tue May 10 15:57:17 2016 Victor Gouet
//

#ifndef TEXTURE_HPP_
# define TEXTURE_HPP_

# include <string>
# include "IrrlichtController.hpp"

class	BomberManTexture
{
public:
  static const std::string ziggsTexture;
  static const std::string ziggsMD;
  
  static const std::string caisseDestructibleTexture;
  static const std::string caisseDestructibleMD;
  
  static const std::string caisseIndestructibleTexture;
  static const std::string caisseIndestructibleMD;
  
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
