//
// Created by veyrie_f on 4/27/16.
//

#include "UIManager.hpp"
#include "UIEventReceiver.hpp"

int main()
{
    UIManager uiManager(IrrlichtController::getDevice());
    UIEventReceiver *uiEventReceiver = new UIEventReceiver(uiManager);

    uiManager.AddButton(irr::core::rect<irr::s32>(0, 0, 170, 50), nullptr, UIElement::GUI_ID_NEW_WINDOW_BUTTON, L"Toto", L"TATA");
    uiManager.AddStaticText(L"Je code avec le cul", irr::core::rect<irr::s32>(100, 200, 300, 300), true, true, nullptr, UIElement::GUI_ID_TEXT,
                            false);

    IrrlichtController::getDevice()->setEventReceiver(uiEventReceiver);

    while (IrrlichtController::getDevice()->run() && IrrlichtController::getDriver())
    {
        if (IrrlichtController::getDevice()->isWindowActive())
        {
            IrrlichtController::getDriver()->beginScene(true, true, irr::video::SColor(0, 200, 200, 200));
            IrrlichtController::getDevice()->getGUIEnvironment()->drawAll();
            IrrlichtController::getDriver()->endScene();
        }
    }

    IrrlichtController::getDevice()->drop();
    return 0;
}