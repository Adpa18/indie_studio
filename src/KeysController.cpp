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

void KeysController::BindAction(ACharacter::ACTION action, irr::EKEY_CODE key)
{
    std::map<ACharacter::ACTION, irr::EKEY_CODE>::iterator it;

    // if key is already bind, assign old bind to it
    for (it = _keycodes.begin(); it != _keycodes.end(); ++it)
    {
        if ((*it).second == key)
        {
            (*it).second = _keycodes[action];
            break;
        }
    }

    // Assigns new key
    _keycodes[action] = key;
}

std::vector<std::string> const &KeysController::ToString() const
{
    std::map<ACharacter::ACTION, irr::EKEY_CODE>::const_iterator it;

    m_toString.clear();
    int i = 0;
    for (it = _keycodes.begin(); it != _keycodes.end(); ++it)
    {
        m_toString.push_back(ACharacter::textAction[i++]);
    }

    return m_toString;
}
