//
// MiniBomb.hpp for MINI in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Fri May 20 16:29:00 2016 Victor Gouet
// Last update Fri May 20 20:04:44 2016 Victor Gouet
//

#ifndef MINIBOMB_HPP_
# define MINIBOMB_HPP_

# include "ABomb.hpp"

class		MiniBomb	: public ABomb
{
public:
  MiniBomb(int id = 1);
  MiniBomb	&operator=(ABomb const *);
  MiniBomb(ABomb const *);
  virtual ~MiniBomb();

public:
  virtual void	willExplose();
  virtual bool		isDestructible() const;
  virtual void		disable();

private:
    bool        killObjects(irr::core::vector2df const &pos);
};

#endif