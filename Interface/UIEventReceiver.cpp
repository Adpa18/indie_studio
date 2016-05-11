//
// Created by veyrie_f on 4/27/16.
//

#include "UIEventReceiver.hpp"
#include "PlayerSelectionBox.hpp"

UIEventReceiver::UIEventReceiver(UIManager const &manager) :
        m_manager(manager), m_device(manager.GetDevice()), m_gameState(SPLASH_SCREEN), m_gameSatePrev(PLAY)
{
    LoadTextures();
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
                if (m_gameState == PLAY)
                {
                    m_gameState = PAUSE;
                    fptr = &UIEventReceiver::DisplayPauseMenu;
                }
                else
                {
                    IrrlichtController::getDevice()->closeDevice();
                }
                break;

            case irr::KEY_RETURN:
                if (m_gameState == SPLASH_SCREEN && event.KeyInput.PressedDown)
                {
                    m_gameState = MAIN_MENU;
                    fptr = &UIEventReceiver::DisplayMainMenu;
                    return true;
                }
                break;

            case irr::KEY_DOWN:
                if (event.KeyInput.PressedDown)
                {
                    SelectNextButton();
                }
                break;

            case irr::KEY_UP:
                if (event.KeyInput.PressedDown)
                {
                    SelectPrevButton();
                }
                break;

            default:
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
                        fptr = &UIEventReceiver::DisplayMainMenu;
                        break;

                    case UIElement::MAIN_MENU_BUTTON_1P:
                        m_gameState = MENU_MAP;
                        fptr = &UIEventReceiver::DisplayMapMenu;
                        break;

                    case UIElement::MAP_SELECTION1:
                        m_gameState = LOADING_SCREEN;
                        fptr = &UIEventReceiver::DisplayLoadingScreen;
                        break;

                    default:
                        break;
                }
                break;

            default:
                return false;
                break;
        }
    }

    // Updates menu visibility according to the current game state
    if (fptr != nullptr)
    {
        m_manager.ClearEnv();
        m_buttons.clear();
        (this->*fptr)();
    }
    fptr = nullptr;

    RefreshButtons();

    return false;
}

// Show the game main menu
void UIEventReceiver::DisplayMainMenu()
{
    irr::gui::IGUIImage *img = m_manager.GetEnv()->addImage(irr::core::rect<irr::s32>(0, 0, IrrlichtController::width, IrrlichtController::height),
                                                            nullptr, UIElement::SPLASH_BACKGROUND, L"", true);

    img->setImage(IrrlichtController::getDevice()->getVideoDriver()->getTexture("../media/PlayerSelection.png"));
    img->setScaleImage(true);

    PlayerSelectionBox playerSelectionBox(&m_manager, "../media/PlayerButton.png",
                                          irr::core::rect<irr::s32>(IrrlichtController::width * 0.014, IrrlichtController::height * 0.445,
                                                                    IrrlichtController::width * 0.24, IrrlichtController::height * 0.85),
                                          UIElement::MAIN_MENU_BUTTON_1P, false);
    playerSelectionBox.Update();

    irr::gui::IGUIButton *b;
    /**b = m_manager.GetEnv()->addButton(irr::core::rect<irr::s32>(IrrlichtController::width * 0.015, IrrlichtController::height * 0.445,
                                                            IrrlichtController::width * 0.24, IrrlichtController::height * 0.85),
                                  nullptr, UIElement::MAIN_MENU_BUTTON_1P, L"One player", L"");*/
    //m_buttons.push_back(b);

    b = m_manager.GetEnv()->addButton(irr::core::rect<irr::s32>(IrrlichtController::width * 0.32, IrrlichtController::height / 2.0 - 50,
                                                                IrrlichtController::width * 0.47, IrrlichtController::height / 2.0 + 50),
                                      nullptr, UIElement::MAIN_MENU_BUTTON_2P, L"Two players", L"");
    b->setImage(m_manager.GetDevice()->getVideoDriver()->getTexture("../media/PlayerSelection.png"));
    //m_buttons.push_back(b);

    b = m_manager.GetEnv()->addButton(irr::core::rect<irr::s32>(IrrlichtController::width * 0.52, IrrlichtController::height / 2.0 - 50,
                                                                IrrlichtController::width * 0.67, IrrlichtController::height / 2.0 + 50),
                                      nullptr, UIElement::MAIN_MENU_BUTTON_3P, L"Three players", L"");
    //m_buttons.push_back(b);

    b = m_manager.GetEnv()->addButton(irr::core::rect<irr::s32>(IrrlichtController::width * 0.72, IrrlichtController::height / 2.0 - 50,
                                                            IrrlichtController::width * 0.87, IrrlichtController::height / 2.0 + 50),
                                  nullptr, UIElement::MAIN_MENU_BUTTON_4P, L"Four players", L"");
    //m_buttons.push_back(b);

    m_gameSatePrev = m_gameState;
}

// Splash screen waiting for player to press some button
void UIEventReceiver::DisplaySplashScreen()
{
    irr::gui::IGUIImage* image = m_manager.GetEnv()->addImage(irr::core::rect<irr::s32>(0, 0, IrrlichtController::width, IrrlichtController::height),
                                                              nullptr, UIElement::SPLASH_BACKGROUND, L"", true);
    image->setImage(IrrlichtController::getDevice()->getVideoDriver()->getTexture("../media/MenuScene.png"));

    image->setScaleImage(true);

    image = m_manager.GetEnv()->addImage(irr::core::rect<irr::s32>(0, 0, IrrlichtController::width, IrrlichtController::height),
                                         nullptr, UIElement::SPLASH_BUTTON_START, L"", true);
    image->setImage(IrrlichtController::getDevice()->getVideoDriver()->getTexture("../media/MenuSceneStart.png"));

    image->setScaleImage(true);

    m_gameSatePrev = m_gameState;
}

/**
 * \brief Map selection
 */
void UIEventReceiver::DisplayMapMenu()
{
    irr::gui::IGUIButton *b1 = m_manager.GetEnv()->addButton(irr::core::rect<irr::s32>(IrrlichtController::width * 0.7, IrrlichtController::height * 0.1,
                                                                                       IrrlichtController::width * 0.95, IrrlichtController::height * 0.3),
                                                             nullptr, UIElement::MAP_SELECTION1, L"Map 1", L"");

    irr::gui::IGUIButton *b2 = m_manager.GetEnv()->addButton(irr::core::rect<irr::s32>(IrrlichtController::width * 0.7, IrrlichtController::height * 0.4,
                                                                                       IrrlichtController::width * 0.95, IrrlichtController::height * 0.6),
                                                             nullptr, UIElement::MAP_SELECTION2, L"Map 2", L"");

    irr::gui::IGUIButton *b3 = m_manager.GetEnv()->addButton(irr::core::rect<irr::s32>(IrrlichtController::width * 0.7, IrrlichtController::height * 0.7,
                                                                                       IrrlichtController::width * 0.95, IrrlichtController::height * 0.9),
                                                             nullptr, UIElement::MAP_SELECTION3, L"Map 3", L"");

    m_buttons.push_back(b1);
    m_buttons.push_back(b2);
    m_buttons.push_back(b3);

    m_gameSatePrev = m_gameState;
}

// Pause menu from pause button
void UIEventReceiver::DisplayPauseMenu()
{
    m_manager.AddButton(irr::core::rect<irr::s32>(IrrlichtController::width / 2.0 - 100, IrrlichtController::height / 2.0 - 50,
                                                  IrrlichtController::width / 2.0 + 100, IrrlichtController::height / 2.0 + 50),
                        nullptr, UIElement::QUIT_BUTTON , L"PRESS START", L"");
    m_gameSatePrev = m_gameState;
}

// Screen displayed between level loading
void UIEventReceiver::DisplayLoadingScreen()
{
    irr::gui::IGUIImage* image = m_manager.GetEnv()->addImage(irr::core::rect<irr::s32>(0, 0, IrrlichtController::width, IrrlichtController::height),
                                                              nullptr, UIElement::SPLASH_BACKGROUND, L"", true);
    image->setImage(IrrlichtController::getDevice()->getVideoDriver()->getTexture("../media/MenuScene.png"));
    m_gameSatePrev = m_gameState;
}

void UIEventReceiver::RefreshButtons()
{
    int i = 0;

    for (std::list<irr::gui::IGUIButton*>::iterator it = m_buttons.begin(); it != m_buttons.end(); ++it, ++i)
    {
        if (i == 0)
        {
            m_manager.GetEnv()->setFocus(*it);
            (*it)->setPressed(true);
        }
    }
}

void UIEventReceiver::SelectNextButton()
{
    if (m_buttons.size() == 0)
        return;
    irr::gui::IGUIButton *b = m_buttons.front();
    m_buttons.pop_front();
    m_buttons.push_back(b);
}

void UIEventReceiver::SelectPrevButton()
{
    if (m_buttons.size() == 0)
        return;
    irr::gui::IGUIButton *b = m_buttons.back();
    m_buttons.pop_back();
    m_buttons.push_front(b);
}

void UIEventReceiver::LoadTextures()
{
    m_manager.GetDevice()->getVideoDriver()->getTexture("../media/MenuScene.png");
    m_manager.GetDevice()->getVideoDriver()->getTexture("../media/PlayerSelection.png");
    m_manager.GetDevice()->getVideoDriver()->getTexture("../media/MenuSceneStart.png");
    m_manager.GetDevice()->getVideoDriver()->getTexture("../media/PlayerSelection.png");
    m_manager.GetDevice()->getVideoDriver()->getTexture("../media/PlayerButton.png");
    m_manager.GetDevice()->getVideoDriver()->getTexture("../media/PlayerButtonIa.png");
}
