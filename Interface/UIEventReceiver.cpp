//
// Created by veyrie_f on 4/27/16.
//

#include "UIEventReceiver.hpp"

UIEventReceiver::UIEventReceiver(UIManager const &manager) :
        m_manager(manager), m_device(manager.GetDevice()), m_gameState(SPLASH_SCREEN), m_gameSatePrev(PLAY)
{
    DisplaySplashScreen();
}

bool UIEventReceiver::OnEvent(const irr::SEvent &event)
{

    if (event.EventType == irr::EET_GUI_EVENT)
    {
        irr::s32 id = event.GUIEvent.Caller->getID();

        switch (event.GUIEvent.EventType)
        {
            case irr::gui::EGET_BUTTON_CLICKED:
                switch (id)
                {
                    case UIElement::SPLASH_BUTTON_START:
                        m_gameState = MAIN_MENU;
                        return true;
                }
                break;

            default:
                return false;
                break;
        }
    }

    // Updates menu visibility according to the current game state
    if (m_gameState == SPLASH_SCREEN && m_gameSatePrev != SPLASH_SCREEN)
    {
        DisplaySplashScreen();
    }
    if (m_gameState == MAIN_MENU && m_gameSatePrev != MAIN_MENU)
    {
        DisplayMainMenu();
    }

    return false;
}

// Show the game main menu
void UIEventReceiver::DisplayMainMenu()
{
    m_manager.ClearEnv();
    m_manager.AddButton(irr::core::rect<irr::s32>(IrrlichtController::width * 0.1, IrrlichtController::height / 2.0 - 50,
                                                  IrrlichtController::width * 0.25, IrrlichtController::height / 2.0 + 50),
                        nullptr, UIElement::MAIN_MENU_BUTTON_1P, L"One player", L"");
    m_manager.AddButton(irr::core::rect<irr::s32>(IrrlichtController::width * 0.30, IrrlichtController::height / 2.0 - 50,
                                                  IrrlichtController::width * 0.45, IrrlichtController::height / 2.0 + 50),
                        nullptr, UIElement::MAIN_MENU_BUTTON_1P, L"Two players", L"");
    m_manager.AddButton(irr::core::rect<irr::s32>(IrrlichtController::width * 0.50, IrrlichtController::height / 2.0 - 50,
                                                  IrrlichtController::width * 0.65, IrrlichtController::height / 2.0 + 50),
                        nullptr, UIElement::MAIN_MENU_BUTTON_1P, L"Three players", L"");
    m_manager.AddButton(irr::core::rect<irr::s32>(IrrlichtController::width * 0.70, IrrlichtController::height / 2.0 - 50,
                                                  IrrlichtController::width * 0.85, IrrlichtController::height / 2.0 + 50),
                        nullptr, UIElement::MAIN_MENU_BUTTON_1P, L"Four players", L"");
    m_gameSatePrev = m_gameState;
}

// Splash screen waiting for player to press some button
void UIEventReceiver::DisplaySplashScreen()
{
    m_manager.ClearEnv();
    m_manager.AddButton(irr::core::rect<irr::s32>(IrrlichtController::width / 2.0 - 100, IrrlichtController::height / 2.0 - 50,
            IrrlichtController::width / 2.0 + 100, IrrlichtController::height / 2.0 + 50), nullptr, UIElement::SPLASH_BUTTON_START, L"PRESS START", L"");

    m_gameSatePrev = m_gameState;
}
