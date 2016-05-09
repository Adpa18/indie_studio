//
// AIteam.hpp for ITEM in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Mon May  9 17:13:25 2016 Victor Gouet
// Last update Mon May  9 18:20:29 2016 Victor Gouet
//

#ifndef AITEM_HPP_
# define AITEM_HPP_

// # include "BomberMap.hpp"
# include "AGameObject.hpp"

class	AItem	: public AGameObject
{
public:
  AItem(irr::core::vector2df const &pos, std::string const &mesh, std::string const &texture, AGameObject::Type type = ITEM);
  virtual ~AItem();

public:
  virtual void	use() = 0;
};

#endif
