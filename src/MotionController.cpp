/*
** MotionController.cpp for cpp_indie_studio
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Fri Apr 29 10:00:02 2016 Adrien WERY
** Last update	Fri Apr 29 10:07:53 2016 Adrien WERY
*/

#include <iostream>
#include "../include/MotionController.hpp"

MotionController::MotionController(irr::SJoystickInfo info) : _info(info)
{
    m_keysToString = {
            "Square",
            "Cross",
            "Circle",
            "Triangle",
            "L1",
            "R1",
            "L2",
            "R2",
            "L2",
            "First Option",
            "Second Option",
            "L3",
            "R3",
            "Home",
            "Other"
    };

    _keycodes = {
            { ACharacter::ACTION::LEFT, ControllerKey::SQUARE },
            { ACharacter::ACTION::RIGHT, ControllerKey::CIRCLE },
            { ACharacter::ACTION::UP, ControllerKey::CIRCLE },
            { ACharacter::ACTION::DOWN, ControllerKey::CIRCLE },
            { ACharacter::ACTION::BOMB, ControllerKey::SQUARE },
            { ACharacter::ACTION::ACT, ControllerKey::CIRCLE },
    };
}

MotionController::~MotionController()
{

}

const irr::SJoystickInfo            &MotionController::getInfo() const
{
    return (this->_info);
}

const irr::SEvent::SJoystickEvent   &MotionController::getData() const
{
    return (this->_data);
}

void                                MotionController::setData(const irr::SEvent::SJoystickEvent data)
{
    this->_data = data;
}

ACharacter::ACTION      MotionController::getDirAxis(const Axis axis) const
{
    irr::f32 moveHorizontal;
    irr::f32 moveVertical;

    switch (axis) {
        case LEFT_JOYSTICK:
            moveHorizontal = (irr::f32)this->_data.Axis[irr::SEvent::SJoystickEvent::AXIS_X] / 32767.f;
            if (moveHorizontal > 0.5f) {
                return (ACharacter::ACTION::RIGHT);
            } else if (moveHorizontal < -0.5f) {
                return (ACharacter::ACTION::LEFT);
            } else {
                moveVertical = (irr::f32)this->_data.Axis[irr::SEvent::SJoystickEvent::AXIS_Y] / -32767.f;
                if (moveVertical > 0.5f) {
                    return (ACharacter::ACTION::UP);
                } else if (moveVertical < -0.5f) {
                    return (ACharacter::ACTION::DOWN);
                }
            }
            break;
        case RIGHT_JOYSTICK:
            break;
        default:
            break;
    }
    return (ACharacter::ACTION::IDLE);
}

bool    MotionController::IsButtonPressed(ControllerKey button) const
{
    return (button == this->_data.ButtonStates);
}

void MotionController::BindAction(ACharacter::ACTION action, MotionController::ControllerKey key)
{
    std::map<ACharacter::ACTION, MotionController::ControllerKey>::iterator it;

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

const std::vector<MotionController::KeyInfo> &MotionController::ToString()
{
    std::map<ACharacter::ACTION, ControllerKey>::const_iterator it;
    std::string toAdd;

    m_toString.clear();
    int i = 0;
    for (it = _keycodes.begin(); it != _keycodes.end(); ++it)
    {
        // The 4 first keys are for directions, thus cannot be mapped
        if (i > 3)
        {
            toAdd = ACharacter::textAction[i];
            for (unsigned long j = toAdd.size(); j < 60; j++)
            {
                toAdd += ".";
            }
            toAdd += m_keysToString[(*it).second];
            std::cout << toAdd.c_str() << std::endl;
            m_toString.push_back(KeyInfo((*it).first, (*it).second, toAdd));
        }
        ++i;
    }
    return m_toString;
}
