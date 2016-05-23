//
// Created by veyrie_f on 4/27/16.
//

#include <unistd.h>
#include "UIEventReceiver.hpp"
#include "../include/Texture.hpp"
#include "../include/GameManager.hpp"
#include "../Video/Video.hpp"

UIEventReceiver::UIEventReceiver(UIManager const &manager) :
        m_manager(manager), m_device(manager.GetDevice())
{
    // LoadTextures();
    DisplaySplashScreen();
}

/*
 * \brief Should return continue if event is completely handled
 */
bool UIEventReceiver::OnEvent(const irr::SEvent &event)
{
    //Permet de ne la load qu'au changement de state
    static int state = -1;
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    {
        switch (event.KeyInput.Key)
        {
            case irr::KEY_ESCAPE:
                if (GameManager::SharedInstance()->getGameState() == GameManager::PAUSE)
                {
                    GameManager::SharedInstance()->setGameState(GameManager::PLAY);
                    IrrlichtController::getDevice()->setEventReceiver(GameManager::SharedInstance()->getEventGame());
                    // fptr = &UIEventReceiver::DisplayPauseMenu;
                    // m_gameState = PAUSE;
                    // return (true);
                    fptr = &UIEventReceiver::DisplayGameHUD;
                }
                else
                {
                    IrrlichtController::getDevice()->closeDevice();
                }
                break;

            case irr::KEY_RETURN:
                if (GameManager::SharedInstance()->getGameState() == GameManager::SPLASH_SCREEN &&
                    event.KeyInput.PressedDown)
                {
                    GameManager::SharedInstance()->setGameState(GameManager::MAIN_MENU);
                    fptr = &UIEventReceiver::DisplayMainMenu;
                    return true;
                }
                break;

            case irr::KEY_SPACE:
                if (m_boxContainer != nullptr)
                {
                    m_boxContainer->PlayerJoin(1);
                    return true;
                }
                break;

            case irr::KEY_DOWN:
                if (event.KeyInput.PressedDown)
                {
                    SelectNextButton();
                    if (m_boxContainer != nullptr)
                    {
                        m_boxContainer->SelectUp();
                    }
                }
                break;

            case irr::KEY_UP:
                if (event.KeyInput.PressedDown)
                {
                    SelectPrevButton();
                    if (m_boxContainer != nullptr)
                    {
                        m_boxContainer->SelectDown();
                    }
                }
                break;

            case irr::KEY_LEFT:
                if (event.KeyInput.PressedDown)
                {
                    if (m_boxContainer != nullptr)
                    {
                        m_boxContainer->SelectLeft();
                    }
                }
                break;

            case irr::KEY_RIGHT:
                if (event.KeyInput.PressedDown)
                {
                    if (m_boxContainer != nullptr)
                    {
                        m_boxContainer->SelectRight();
                    }
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
		       BomberMap::deleteMap();
		       state = -1;
                        GameManager::SharedInstance()->setGameState(GameManager::MAIN_MENU);
                        fptr = &UIEventReceiver::DisplayMainMenu;
                        break;

                    case UIElement::MAIN_MENU_BUTTON_1P:
		      //BomberMap::deleteMap();
                        GameManager::SharedInstance()->setGameState(GameManager::MENU_MAP);
                        fptr = &UIEventReceiver::DisplayMapMenu;
                        break;

                    case UIElement::MAP_SELECTION1:
		      // BomberMap::deleteMap();
                        fptr = &UIEventReceiver::DisplayGameHUD;
                        GameManager::SharedInstance()->setFptr(&GameManager::willStartGame);
                        GameManager::SharedInstance()->setGameState(GameManager::PLAY);
                        break;

                    case UIElement::CONTINUE:
                        fptr = &UIEventReceiver::DisplayGameHUD;
                        IrrlichtController::getDevice()->setEventReceiver(
                                GameManager::SharedInstance()->getEventGame());
                        GameManager::SharedInstance()->setGameState(GameManager::PLAY);
                        break;

                    default:
                        break;
                }
                break;

            case irr::gui::EGET_ELEMENT_FOCUSED:
                switch (id)
                {
                    case UIElement::MAP_SELECTION1:
                        if (state != 0)
                        {
			                std::cout << "SMALL" << std::endl;
                            state = 0;
                            BomberMap::deleteMap();
			    // BomberMap::createMapFromSave("tmpSaveMap/MapSave2016-05-23.17:35:36.xml");
                            BomberMap::newMap("./media/smallMap/map1.xml");
			    BomberMap::getMap()->genMap();
                        }
                        break;

                    case UIElement::MAP_SELECTION2:
                        if (state != 1)
                        {
			                std::cout << "MEDIUM" << std::endl;
                            state = 1;
                            BomberMap::deleteMap();
                            BomberMap::newMap("./media/smallMap/map1.xml");
                            BomberMap::getMap()->genMap();
                        }
                        break;

                    case UIElement::MAP_SELECTION3:
                        if (state != 2)
                        {
			                std::cout << "LARGE" << std::endl;
                            state = 2;
                            BomberMap::deleteMap();
                            BomberMap::newMap("./media/smallMap/map1.xml");
                            BomberMap::getMap()->genMap();
                        }
                      break;

                    // For the player selection menu
                    case UIElement::MAIN_MENU_BUTTON_1P:
                    case UIElement::MAIN_MENU_BUTTON_2P:
                    case UIElement::MAIN_MENU_BUTTON_3P:
                    case UIElement::MAIN_MENU_BUTTON_4P:
                        if (m_boxContainer != nullptr)
                        {
                            m_boxContainer->UpdateBoxes(id);
                        }
                        break;

                    default:
                        break;
                }
                return false;
                break;

            default:
                return false;
                break;
        }
    }

    // Updates menu visibility according to the current game state
    if (fptr != nullptr)
    {
        if (m_boxContainer != nullptr)
        {
            delete m_boxContainer;
            m_boxContainer = nullptr;
        }
        m_manager.ClearEnv();
        m_buttons.clear();
        (this->*fptr)();
        GameManager::SharedInstance()->setPrevGameState(GameManager::SharedInstance()->getGameState());
    }
    fptr = nullptr;

    RefreshButtons();

    return false;
}

void UIEventReceiver::DisplayGameHUD()
{
}

// Show the game main menu
void UIEventReceiver::DisplayMainMenu()
{
    irr::gui::IGUIImage *img = m_manager.GetEnv()->addImage(
            irr::core::rect<irr::s32>(0, 0, IrrlichtController::width, IrrlichtController::height),
            nullptr, UIElement::SPLASH_BACKGROUND, L"", true);

    img->setImage(IrrlichtController::getDevice()->getVideoDriver()->getTexture(
            BomberManTexture::getModel("playerSelection").texture.c_str()));
    img->setScaleImage(true);

    m_boxContainer = new PlayerSelectionBoxContainer(&m_manager);
}

// Splash screen waiting for player to press some button
void UIEventReceiver::DisplaySplashScreen()
{
    Video *video = new Video();

    video->Run();
    delete video;
    irr::gui::IGUIImage *image = m_manager.GetEnv()->addImage(
            irr::core::rect<irr::s32>(0, 0, IrrlichtController::width, IrrlichtController::height),
            nullptr, UIElement::SPLASH_BACKGROUND, L"", true);
    image->setImage(IrrlichtController::getDevice()->getVideoDriver()->getTexture(
            BomberManTexture::getModel("menuScene").texture.c_str()));

    image->setScaleImage(true);

    image = m_manager.GetEnv()->addImage(
            irr::core::rect<irr::s32>(0, 0, IrrlichtController::width, IrrlichtController::height),
            nullptr, UIElement::SPLASH_BUTTON_START, L"", true);
    image->setImage(IrrlichtController::getDevice()->getVideoDriver()->getTexture(
            BomberManTexture::getModel("menuSceneStart").texture.c_str()));

    image->setScaleImage(true);
}

/**
 * \brief Map selection
 */
void UIEventReceiver::DisplayMapMenu()
{
    irr::gui::IGUIButton *b1 = m_manager.GetEnv()->addButton(
            irr::core::rect<irr::s32>(IrrlichtController::width * 0.7, IrrlichtController::height * 0.1,
                                      IrrlichtController::width * 0.95, IrrlichtController::height * 0.3),
            nullptr, UIElement::MAP_SELECTION1, L"Map 1", L"");

    irr::gui::IGUIButton *b2 = m_manager.GetEnv()->addButton(
            irr::core::rect<irr::s32>(IrrlichtController::width * 0.7, IrrlichtController::height * 0.4,
                                      IrrlichtController::width * 0.95, IrrlichtController::height * 0.6),
            nullptr, UIElement::MAP_SELECTION2, L"Map 2", L"");

    irr::gui::IGUIButton *b3 = m_manager.GetEnv()->addButton(
            irr::core::rect<irr::s32>(IrrlichtController::width * 0.7, IrrlichtController::height * 0.7,
                                      IrrlichtController::width * 0.95, IrrlichtController::height * 0.9),
            nullptr, UIElement::MAP_SELECTION3, L"Map 3", L"");

    m_buttons.push_back(b1);
    m_buttons.push_back(b2);
    m_buttons.push_back(b3);
}

// Pause menu from pause button
void UIEventReceiver::DisplayPauseMenu()
{
    m_buttons.push_back(m_manager.GetEnv()->addButton(irr::core::rect<irr::s32>(IrrlichtController::width / 2.0 - 100,
                                                  IrrlichtController::height / 2.5 - 50,
                                                  IrrlichtController::width / 2.0 + 100,
                                                  IrrlichtController::height / 2.5 + 50),
                        nullptr, UIElement::CONTINUE, L"Continue", L""));

    m_buttons.push_back(m_manager.GetEnv()->addButton(irr::core::rect<irr::s32>(IrrlichtController::width / 2.0 - 100,
                                                  IrrlichtController::height / 2.0 - 50,
                                                  IrrlichtController::width / 2.0 + 100,
                                                  IrrlichtController::height / 2.0 + 50),
                        nullptr, UIElement::SPLASH_BUTTON_START, L"Menu", L""));

    m_buttons.push_back(m_manager.GetEnv()->addButton(irr::core::rect<irr::s32>(IrrlichtController::width / 2.0 - 100,
                                                  IrrlichtController::height / 1.66 - 50,
                                                  IrrlichtController::width / 2.0 + 100,
                                                  IrrlichtController::height / 1.66 + 50),
                        nullptr, UIElement::SPLASH_BUTTON_START, L"Quitter", L""));
}

// Screen displayed between level loading
void UIEventReceiver::DisplayLoadingScreen()
{
    irr::gui::IGUIImage *image = m_manager.GetEnv()->addImage(
            irr::core::rect<irr::s32>(0, 0, IrrlichtController::width, IrrlichtController::height),
            nullptr, UIElement::SPLASH_BACKGROUND, L"", true);
    image->setImage(IrrlichtController::getDevice()->getVideoDriver()->getTexture(
            BomberManTexture::getModel("menuScene").texture.c_str()));
}

void UIEventReceiver::RefreshButtons()
{
    int i = 0;

    for (std::list<irr::gui::IGUIButton *>::iterator it = m_buttons.begin(); it != m_buttons.end(); ++it, ++i)
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

