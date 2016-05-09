//
// ItemThrow.hpp for ITEM THROW in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Mon May  9 17:39:34 2016 Victor Gouet
// Last update Mon May  9 21:32:05 2016 Victor Gouet
//

#ifndef ITEMTHROW_HPP_
# define ITEMTHROW_HPP_

# include "AItem.hpp"

class	ItemThrow	: public AItem
{
public:
  ItemThrow(irr::core::vector2df const &);
  virtual ~ItemThrow();

public:
  virtual void		use();
};

#endif
