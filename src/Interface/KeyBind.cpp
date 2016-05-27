//
// Created by veyrie_f on 27/05/16.
//

#include "KeyBind.h"

KeyBind::KeyBind()
{

}

KeyBind::~KeyBind()
{

}

ACharacter::ACTION KeyBind::GetAction(MotionController::ControllerKey key) const
{
    return m_binds[key];
}

std::map<MotionController::ControllerKey, ACharacter::ACTION> const &KeyBind::GetAllActions() const
{
    return m_binds;
}

void KeyBind::BindAction(MotionController::ControllerKey key, ACharacter::ACTION action)
{
    // if key is already bind, remove it and assign new
    m_binds[key] = action;
}
