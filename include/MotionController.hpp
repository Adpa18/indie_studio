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

public:
    enum Controller {
        SQUARE = 1 << 0,
        CROSS = 1 << 1,
        CIRCLE = 1 << 2,
        TRIANGLE = 1 << 3,
        L1 = 1 << 4,
        R1 = 1 << 5,
        L2 = 1 << 6,
        R2 = 1 << 7,
        FIRST_OPTION = 1 << 7,
        SECOND_OPTION = 1 << 8,
        L3 = 1 << 9,
        R3 = 1 << 10,
        HOME = 1 << 11,
        OTHER = 1 << 12
    };
};

#endif /* !MOTIONCONTROLLER_HPP */
