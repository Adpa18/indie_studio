//
// Created by veyrie_f on 27/05/16.
//

#ifndef CPP_INDIE_STUDIO_KEYBIND_H
#define CPP_INDIE_STUDIO_KEYBIND_H

#include <map>
#include "../../include/MotionController.hpp"

/*
 * \brief This class will holds all the informations about the key bindings used by the players
 */
class KeyBind
{
public:
    KeyBind();
    virtual ~KeyBind();

public:
    ACharacter::ACTION GetAction(MotionController::ControllerKey key) const;
    void BindAction(MotionController::ControllerKey key, ACharacter::ACTION action);
    std::map<MotionController::ControllerKey, ACharacter::ACTION> const& GetAllActions() const;

private:
    std::map<MotionController::ControllerKey, ACharacter::ACTION> m_binds;
};


#endif //CPP_INDIE_STUDIO_KEYBIND_H
