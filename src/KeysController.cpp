/*
** KeysController.cpp for cpp_indie_studio
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Fri Apr 29 10:00:02 2016 Adrien WERY
** Last update	Fri Apr 29 10:52:18 2016 Adrien WERY
*/

#include "../include/KeysController.hpp"

KeysController::KeysController(std::map<ACharacter::ACTION, irr::EKEY_CODE> const &keycodes) : _keycodes(keycodes)
{

}

KeysController::~KeysController()
{
}

std::map<ACharacter::ACTION, irr::EKEY_CODE> const  &KeysController::getKeycodes() const
{
    return (this->_keycodes);
}
