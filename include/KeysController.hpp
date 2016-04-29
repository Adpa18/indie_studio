/*
** KeysController.hpp for cpp_indie_studio
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Fri Apr 29 09:58:12 2016 Adrien WERY
** Last update	Fri Apr 29 10:30:02 2016 Adrien WERY
*/

#ifndef KEYSCONTROLLER_HPP
# define KEYSCONTROLLER_HPP

# include "AController.hpp"
# include "ACharacter.hpp"
# include <map>

class KeysController : public AController {
private:
    std::map<ACharacter::ACTION, irr::EKEY_CODE> const &    _keycodes;
public:
    KeysController (std::map<ACharacter::ACTION, irr::EKEY_CODE> const &keycodes);
    virtual ~KeysController ();
    std::map<ACharacter::ACTION, irr::EKEY_CODE> const  &getKeycodes() const;
};

#endif /* !KEYSCONTROLLER_HPP */
