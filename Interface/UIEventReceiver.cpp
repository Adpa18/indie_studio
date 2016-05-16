//
// Created by veyrie_f on 4/27/16.
//

#include <unistd.h>
#include "UIEventReceiver.hpp"
#include "../include/Texture.hpp"
#include "../include/GameManager.hpp"

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
	      if (GameManager::SharedInstance()->getGameState() == GameManager::SPLASH_SCREEN && event.KeyInput.PressedDown)
                {
		  GameManager::SharedInstance()->setGameState(GameManager::MAIN_MENU);
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
		      GameManager::SharedInstance()->setGameState(GameManager::MAIN_MENU);
                        fptr = &UIEventReceiver::DisplayMainMenu;
                        break;

                    case UIElement::MAIN_MENU_BUTTON_1P:
		      GameManager::SharedInstance()->setGameState(GameManager::MENU_MAP);
                        fptr = &UIEventReceiver::DisplayMapMenu;
                        break;

                    case UIElement::MAP_SELECTION1:
                        fptr = &UIEventReceiver::DisplayGameHUD;
			GameManager::SharedInstance()->setFptr(&GameManager::willStartGame);
			GameManager::SharedInstance()->setGameState(GameManager::PLAY);
                        break;
		     
		case UIElement::CONTINUE:
		  fptr = &UIEventReceiver::DisplayGameHUD;
		  IrrlichtController::getDevice()->setEventReceiver(GameManager::SharedInstance()->getEventGame());
		  GameManager::SharedInstance()->setGameState(GameManager::PLAY);
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
        if (m_boxContainer != nullptr)
        {
            delete m_boxContainer;
            m_boxContainer = nullptr;
        }
        (this->*fptr)();
    }
    fptr = nullptr;

    RefreshButtons();

    return false;
}

void UIEventReceiver::DisplayGameHUD()
{
  std::cout << "ALORS " << std::endl;
}

// Show the game main menu
void UIEventReceiver::DisplayMainMenu()
{
    irr::gui::IGUIImage *img = m_manager.GetEnv()->addImage(irr::core::rect<irr::s32>(0, 0, IrrlichtController::width, IrrlichtController::height),
                                                            nullptr, UIElement::SPLASH_BACKGROUND, L"", true);

    img->setImage(IrrlichtController::getDevice()->getVideoDriver()->getTexture(BomberManTexture::getModel("playerSelection").texture.c_str()));
    img->setScaleImage(true);

    m_boxContainer = new PlayerSelectionBoxContainer(&m_manager);

    GameManager::SharedInstance()->setPrevGameState(GameManager::SharedInstance()->getGameState());
      //m_gameSatePrev = m_gameState;
}

// Splash screen waiting for player to press some button
void UIEventReceiver::DisplaySplashScreen()
{
    irr::gui::IGUIImage* image = m_manager.GetEnv()->addImage(irr::core::rect<irr::s32>(0, 0, IrrlichtController::width, IrrlichtController::height),
                                                              nullptr, UIElement::SPLASH_BACKGROUND, L"", true);
    image->setImage(IrrlichtController::getDevice()->getVideoDriver()->getTexture(BomberManTexture::getModel("menuScene").texture.c_str()));

    image->setScaleImage(true);

    image = m_manager.GetEnv()->addImage(irr::core::rect<irr::s32>(0, 0, IrrlichtController::width, IrrlichtController::height),
                                         nullptr, UIElement::SPLASH_BUTTON_START, L"", true);
    image->setImage(IrrlichtController::getDevice()->getVideoDriver()->getTexture(BomberManTexture::getModel("menuSceneStart").texture.c_str()));

    image->setScaleImage(true);

    GameManager::SharedInstance()->setPrevGameState(GameManager::SharedInstance()->getGameState());
    //m_gameSatePrev = m_gameState;
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

    GameManager::SharedInstance()->setPrevGameState(GameManager::SharedInstance()->getGameState());

    //m_gameSatePrev = m_gameState;
}

// Pause menu from pause button
void UIEventReceiver::DisplayPauseMenu()
{
  m_manager.AddButton(irr::core::rect<irr::s32>(IrrlichtController::width / 2.0 - 100,
						IrrlichtController::height / 2.5 - 50,
						IrrlichtController::width / 2.0 + 100,
						IrrlichtController::height / 2.5 + 50),
		      nullptr, UIElement::CONTINUE , L"Continue", L"");

  m_manager.AddButton(irr::core::rect<irr::s32>(IrrlichtController::width / 2.0 - 100,
						IrrlichtController::height / 2.0 - 50,
						IrrlichtController::width / 2.0 + 100,
						IrrlichtController::height / 2.0 + 50),
		      nullptr, UIElement::SPLASH_BUTTON_START , L"Menu", L"");

  m_manager.AddButton(irr::core::rect<irr::s32>(IrrlichtController::width / 2.0 - 100,
						IrrlichtController::height / 1.8 - 50,
						IrrlichtController::width / 2.0 + 100,
						IrrlichtController::height / 1.8 + 50),
		      nullptr, UIElement::SPLASH_BUTTON_START , L"Menu", L"");
  
    //   m_gameSatePrev = m_gameState;
  GameManager::SharedInstance()->setPrevGameState(GameManager::SharedInstance()->getGameState());
}

// Screen displayed between level loading
void UIEventReceiver::DisplayLoadingScreen()
{
    irr::gui::IGUIImage* image = m_manager.GetEnv()->addImage(irr::core::rect<irr::s32>(0, 0, IrrlichtController::width, IrrlichtController::height),
                                                              nullptr, UIElement::SPLASH_BACKGROUND, L"", true);
    image->setImage(IrrlichtController::getDevice()->getVideoDriver()->getTexture(BomberManTexture::getModel("menuScene").texture.c_str()));

    //    m_gameSatePrev = m_gameState;
    GameManager::SharedInstance()->setPrevGameState(GameManager::SharedInstance()->getGameState());
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
    // m_manager.GetDevice()->getVideoDriver()->getTexture("../media/MenuScene.png");
    // m_manager.GetDevice()->getVideoDriver()->getTexture("../media/PlayerSelection.png");
    // m_manager.GetDevice()->getVideoDriver()->getTexture("../media/MenuSceneStart.png");
    // m_manager.GetDevice()->getVideoDriver()->getTexture("../media/PlayerSelection.png");
    // m_manager.GetDevice()->getVideoDriver()->getTexture("../media/PlayerButton.png");
    // m_manager.GetDevice()->getVideoDriver()->getTexture("../media/PlayerButtonIa.png");
}
