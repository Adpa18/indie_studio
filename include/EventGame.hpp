/*
** EventGame.hpp for cpp_indie_studio
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Apr 27 15:16:51 2016 Adrien WERY
** Last update	Wed Apr 27 15:23:40 2016 Adrien WERY
*/

#ifndef EVENT_HPP
# define EVENT_HPP

# include "IrrlichtController.hpp"
# include <map>

class EventGame : public irr::IEventReceiver {
private:
    bool    KeyIsDown[irr::KEY_KEY_CODES_COUNT];
    std::map<irr::EKEY_CODE, irr::EKEY_ACTION> _keycodes;
    irr::SEvent::SJoystickEvent  JoystickState;
public:
    EventGame ();
    virtual ~EventGame ();
    virtual bool  OnEvent(const irr::SEvent& event);
    virtual bool  IsKeyDown(irr::EKEY_CODE keyCode) const;
    const irr::SEvent::SJoystickEvent &GetJoystickState(void) const;
};

#endif /* !EVENT_HPP */
