//
// Created by veyrie_f on 4/27/16.
//

#ifndef CPP_INDIE_STUDIO_UIEVENTRECEIVER_HPP
#define CPP_INDIE_STUDIO_UIEVENTRECEIVER_HPP

#include <iostream>
#include "../Irrlicht/irrlicht-1.8.3/include/irrlicht.h"
#include "UIElements.hpp"
#include "UIManager.hpp"

// Event receiver for ui
class UIEventReceiver : public irr::IEventReceiver
{
public:
    UIEventReceiver(UIManager const& manager) : m_manager(manager), m_device(manager.GetDevice())
    {}

    virtual bool OnEvent(const irr::SEvent &event)
    {
        if (event.EventType == irr::EET_GUI_EVENT)
        {
            irr::s32 id = event.GUIEvent.Caller->getID();
            irr::gui::IGUIEnvironment *env = m_device->getGUIEnvironment();
            switch (event.GUIEvent.EventType)
            {
                case irr::gui::EGET_SCROLL_BAR_CHANGED:
                    break;

                case irr::gui::EGET_BUTTON_CLICKED:
                    switch (id)
                    {
                        case UIElement::GUI_ID_QUIT_BUTTON:
                            m_device->closeDevice();
                            return true;

                        case UIElement::GUI_ID_NEW_WINDOW_BUTTON:
                        {
                            m_manager.GetElementFromID(UIElement::GUI_ID_TEXT)->setText(L"lalalalalalaaaaaa");
                        }
                    }
                    break;

                case irr::gui::EGET_FILE_SELECTED:
                {
                }
                    break;

                default:
                    break;
            }
        }

        return false;
    }

private:
    UIManager m_manager;
    irr::IrrlichtDevice *m_device;
};


#endif //CPP_INDIE_STUDIO_UIEVENTRECEIVER_HPP
