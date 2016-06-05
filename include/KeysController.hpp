/*
** KeysController.hpp for cpp_indie_studio
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Fri Apr 29 09:58:12 2016 Adrien WERY
** Last update	Fri Apr 29 10:30:02 2016 Adrien WERY
*/

#ifndef KEYSCONTROLLER_HPP
# define KEYSCONTROLLER_HPP

# include <map>
# include "AController.hpp"
# include "ACharacter.hpp"
# include "MotionController.hpp"

/*
 * \brief This class will holds all the informations about the key bindings used by the players
 */
class KeysController : public AController {
private:
    std::map<ACharacter::ACTION, irr::EKEY_CODE> _keycodes;

public:
    /*
     * Storage class for key infos
     */
    // TODO: new class for this templated
    class KeyInfo
    {
    public:
        KeyInfo(ACharacter::ACTION action, irr::EKEY_CODE keycode, std::string const& toString) :
                m_action(action),
                m_keycode(keycode),
                m_toString(toString)
        {

        }

        ~KeyInfo()
        {

        }

        std::string const& ToString()
        {
            return m_toString;
        }

        ACharacter::ACTION GetAction() const
        {
            return m_action;
        }

        irr::EKEY_CODE GetKeycode() const
        {
            return m_keycode;
        }

    private:
        ACharacter::ACTION m_action;
        irr::EKEY_CODE m_keycode;
        std::string m_toString;
    };

public:
    KeysController (std::map<ACharacter::ACTION, irr::EKEY_CODE> const &keycodes);
    virtual ~KeysController ();
    std::map<ACharacter::ACTION, irr::EKEY_CODE> const  &getKeycodes() const;
    std::vector<KeyInfo> const& ToString() const;

public:
    void BindAction(ACharacter::ACTION action, irr::EKEY_CODE key);

private:
    mutable std::vector<KeyInfo> m_toString;
};

#endif /* !KEYSCONTROLLER_HPP */
