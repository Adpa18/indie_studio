/*
** EventGame.hpp for cpp_indie_studio
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Apr 27 15:16:51 2016 Adrien WERY
** Last update	Fri Apr 29 10:48:42 2016 Adrien WERY
*/

#ifndef EVENT_HPP
# define EVENT_HPP

# include "IrrlichtController.hpp"
# include "MotionController.hpp"
# include "KeysController.hpp"
# include "ACharacter.hpp"
# include <vector>
# include <utility>
# include <map>

class EventGame : public irr::IEventReceiver {

public:
    static const std::vector<std::map<ACharacter::ACTION, irr::EKEY_CODE>> _keycodes;

private:
    mutable bool    KeyIsDown[irr::KEY_KEY_CODES_COUNT];
    std::map<int, MotionController *>   _joysticks;
    std::vector<KeysController *>       _keymaps;

public:
  EventGame ();
  virtual ~EventGame ();
  virtual bool  OnEvent(const irr::SEvent& event);
  virtual bool  IsKeyDown(irr::EKEY_CODE keyCode) const;
  bool		IsKeyDownOneTime(irr::EKEY_CODE keyCode) const;
  const MotionController  *GetAvaibleJoystick() const;
  const KeysController    *GetAvaibleKeycodes() const;
};

#endif /* !EVENT_HPP */
