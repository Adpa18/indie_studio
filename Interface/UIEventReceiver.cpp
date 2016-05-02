//
// Created by veyrie_f on 4/27/16.
//

#include "UIEventReceiver.hpp"

UIEventReceiver::UIEventReceiver(UIManager const &manager) :
        m_manager(manager), m_device(manager.GetDevice()), m_gameState(SPLASH_SCREEN), m_gameSatePrev(PLAY)
{
    DisplaySplashScreen();
}

/*
 * \brief Should return continue if event is completely handled
 */
bool UIEventReceiver::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    {
        switch (event.KeyInput.Key)
        {
            case irr::KEY_ESCAPE:
                std::cout << "ESCAPE" << std::endl;
                m_gameState = PAUSE;
                IrrlichtController::getDevice()->closeDevice();
                break;
        }
    }

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
                        break;

                    case UIElement::MAIN_MENU_BUTTON_1P:
                        m_gameState = MENU_MAP;
                        break;

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
        return true;
    }
    if (m_gameState == MAIN_MENU && m_gameSatePrev != MAIN_MENU)
    {
        DisplayMainMenu();
        return true;
    }
    if (m_gameState == MENU_MAP && m_gameSatePrev != MENU_MAP)
    {
        DisplayMapMenu();
        return true;
    }
    if (m_gameState == PAUSE && m_gameSatePrev != PAUSE)
    {
        DisplayPauseMenu();
        return true;
    }

    return false;
}

// Show the game main menu
void UIEventReceiver::DisplayMainMenu()
{
    m_manager.ClearEnv();
    m_manager.AddButton(irr::core::rect<irr::s32>(IrrlichtController::width * 0.12, IrrlichtController::height / 2.0 - 50,
                                                  IrrlichtController::width * 0.27, IrrlichtController::height / 2.0 + 50),
                        nullptr, UIElement::MAIN_MENU_BUTTON_1P, L"One player", L"");
    m_manager.AddButton(irr::core::rect<irr::s32>(IrrlichtController::width * 0.32, IrrlichtController::height / 2.0 - 50,
                                                  IrrlichtController::width * 0.47, IrrlichtController::height / 2.0 + 50),
                        nullptr, UIElement::MAIN_MENU_BUTTON_2P, L"Two players", L"");
    m_manager.AddButton(irr::core::rect<irr::s32>(IrrlichtController::width * 0.52, IrrlichtController::height / 2.0 - 50,
                                                  IrrlichtController::width * 0.67, IrrlichtController::height / 2.0 + 50),
                        nullptr, UIElement::MAIN_MENU_BUTTON_3P, L"Three players", L"");
    m_manager.AddButton(irr::core::rect<irr::s32>(IrrlichtController::width * 0.72, IrrlichtController::height / 2.0 - 50,
                                                  IrrlichtController::width * 0.87, IrrlichtController::height / 2.0 + 50),
                        nullptr, UIElement::MAIN_MENU_BUTTON_4P, L"Four players", L"");
    m_gameSatePrev = m_gameState;
}

// Splash screen waiting for player to press some button
void UIEventReceiver::DisplaySplashScreen()
{
    m_manager.ClearEnv();

    irr::gui::IGUIImage* image = m_manager.GetEnv()->addImage(irr::core::rect<irr::s32>(0, 0, IrrlichtController::width, IrrlichtController::height), nullptr, UIElement::SPLASH_BACKGROUND, L"", true);
    image->setImage(IrrlichtController::getDevice()->getVideoDriver()->getTexture("../media/MenuSceneTEXT.png"));
    m_manager.AddButton(irr::core::rect<irr::s32>(IrrlichtController::width / 2.0 - 100, IrrlichtController::height / 2.0 - 50,
            IrrlichtController::width / 2.0 + 100, IrrlichtController::height / 2.0 + 50), nullptr, UIElement::SPLASH_BUTTON_START, L"PRESS START", L"");

    m_gameSatePrev = m_gameState;
}

void UIEventReceiver::DisplayMapMenu()
{
    m_manager.ClearEnv();
    m_manager.AddButton(irr::core::rect<irr::s32>(IrrlichtController::width / 2.0 + 100, IrrlichtController::height / 2.0 - 50,
                                                  IrrlichtController::width / 2.0 + 300, IrrlichtController::height / 2.0 + 50),
                        nullptr, UIElement::MAP_SELECTION1, L"Map 1", L"");
    m_gameSatePrev = m_gameState;
}

void UIEventReceiver::DisplayPauseMenu()
{
    m_manager.ClearEnv();
    m_manager.AddButton(irr::core::rect<irr::s32>(IrrlichtController::width / 2.0 - 100, IrrlichtController::height / 2.0 - 50,
                                                  IrrlichtController::width / 2.0 + 100, IrrlichtController::height / 2.0 + 50),
                        nullptr, UIElement::QUIT_BUTTON , L"PRESS START", L"");
    m_gameSatePrev = m_gameState;
}
