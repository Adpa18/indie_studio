/*
** AController.hpp for cpp_indie_studio
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Fri Apr 29 09:58:12 2016 Adrien WERY
** Last update	Fri Apr 29 10:04:57 2016 Adrien WERY
*/

#ifndef ACONTROLLER_HPP
# define ACONTROLLER_HPP

# include "IrrlichtController.hpp"

class AController {
private:
    mutable bool    _used;
public:
    AController ();
    virtual ~AController ();
    bool    isUsed() const;
    void    useIt();
  void		stopUseIt() const;
};

#endif /* !ACONTROLLER_HPP */
