/*
** MotionController.cpp for cpp_indie_studio
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Fri Apr 29 10:00:02 2016 Adrien WERY
** Last update	Fri Apr 29 10:07:53 2016 Adrien WERY
*/

#include "../include/MotionController.hpp"

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
