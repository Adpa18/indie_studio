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
#include "MotionController.hpp"
#include "ACharacter.hpp"

MotionController::MotionController(irr::SJoystickInfo info) : _info(info)
{

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