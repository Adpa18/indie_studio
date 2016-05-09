//
// BombFactory.hpp for FACTORY in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Fri Apr 29 14:04:37 2016 Victor Gouet
// Last update Mon May  9 16:18:31 2016 Victor Gouet
//

#ifndef BOMBFACTORY_HPP_
# define BOMBFACTORY_HPP_

# include "BombContainer.hpp"
# include "FireBomb.hpp"

class		BombFactory
{
public:
  template<class T>
  static void	AddBomb(BombContainer &container)
  {
    if (container.getBombsNbr() == 0)
      container.addBomb(new T());
    else
      {
	std::vector<ABomb *>::const_iterator	cont = container.getBombs().begin();
	container.addBomb(new T((*cont)));
      }
  }

  template<class T>
  static BombContainer	*CreateBombContainer()
  {
    BombContainer	*container = new BombContainer();

    AddBomb<T>(*container);
    return (container);
  }

  template<class T>
  static void		ChangeBombContainer(BombContainer &bombContainer)
  {
    std::vector<ABomb *>	const	&bombs = bombContainer.getBombs();
    size_t				size = bombContainer.getBombsNbr();
    size_t				i = 0;
    
    if (bombs.size() == 0)
      return ;
    bombContainer.deleteAllBomb();
    while (i < size)
      {
	bombContainer.addBomb(new T());
	++i;
      }
  }

};

#endif
