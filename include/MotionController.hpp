/*
** MotionController.hpp for cpp_indie_studio
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Fri Apr 29 09:58:12 2016 Adrien WERY
** Last update	Fri Apr 29 10:07:47 2016 Adrien WERY
*/

#ifndef MOTIONCONTROLLER_HPP
# define MOTIONCONTROLLER_HPP

# include "AController.hpp"

class MotionController : public AController {
private:
    irr::SJoystickInfo          _info;
    irr::SEvent::SJoystickEvent _data;
public:
    MotionController (irr::SJoystickInfo info);
    virtual ~MotionController ();
    const irr::SJoystickInfo            &getInfo() const;
    const irr::SEvent::SJoystickEvent   &getData() const;
    void                                setData(irr::SEvent::SJoystickEvent data);
};

#endif /* !MOTIONCONTROLLER_HPP */
