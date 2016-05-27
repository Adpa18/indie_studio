//
// Created by veyrie_f on 4/27/16.
//

#include <dirent.h>
#include <algorithm>
#include "../../include/UIEventReceiver.hpp"
#include "../../include/Texture.hpp"
#include "../../include/GameManager.hpp"
#include "../../include/SoundManager.hpp"
#include "../../include/KeySelectionBox.hpp"

UIEventReceiver::UIEventReceiver(UIManager const &manager) :
        m_manager(manager), m_device(manager.GetDevice())
{
    irr::core::array<irr::SJoystickInfo>    joystickInfo;

    if (IrrlichtController::getDevice()->activateJoysticks(joystickInfo))
    {
        for (size_t i = 0; i < joystickInfo.size(); i++)
        {
            if (joystickInfo[i].Axes > 0 && joystickInfo[i].Buttons > 0)
            {
                m_joysticks[i] = new MotionController(joystickInfo[i]);
            }
        }
    }
    for (std::vector<std::map<ACharacter::ACTION, irr::EKEY_CODE>>::const_iterator it = EventGame::_keycodes.begin(); it != EventGame::_keycodes.end(); ++it)
    {
        m_keymaps.push_back(new KeysController(*it));
    }

    for (irr::u32 i=0; i < irr::KEY_KEY_CODES_COUNT; ++i)
    {
        KeyIsDown[i] = false;
    }

    // Sets callbacks for GUI
    m_guiEvents[irr::gui::EGET_LISTBOX_CHANGED] = &UIEventReceiver::OnListBox;
    m_guiEvents[irr::gui::EGET_LISTBOX_SELECTED_AGAIN] = &UIEventReceiver::OnListBox;
    m_guiEvents[irr::gui::EGET_BUTTON_CLICKED] = &UIEventReceiver::OnButtonClicked;
    m_guiEvents[irr::gui::EGET_ELEMENT_FOCUSED] = &UIEventReceiver::OnElementFocused;
    SoundManager::getManager()->play("welcome.wav");
    SoundManager::getManager()->play("menu.wav", 0, true, 0.1);
    DisplaySplashScreen();
}

UIEventReceiver::~UIEventReceiver()
{
    if (m_boxContainer != nullptr)
    {
        delete m_boxContainer;
    }

    for (std::map<int, MotionController *>::iterator it = m_joysticks.begin(); it != m_joysticks.end(); ++it)
    {
        delete (*it).second;
    }

    for (std::vector<KeysController *>::iterator it = m_keymaps.begin(); it != m_keymaps.end(); ++it)
    {
        delete (*it);
    }
}

/*
 * \brief Should return continue if event is completely handled
 */
bool UIEventReceiver::OnEvent(const irr::SEvent &event_copy)
{
    // Update joysticks inputs
    HandleJoysticks(event_copy);

    // Key inputs
    EVENT_STATE eventState = OnKeyInput(event_copy);
    if (eventState == HANDELD) return true;
    if (eventState == NOT_HANDLED) return false;

    // GUI events
    if (event_copy.EventType == irr::EET_GUI_EVENT)
    {
        eventState = OnGUIEvent(event_copy);
        if (eventState == HANDELD) return true;
        if (eventState == NOT_HANDLED) return false;
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
    SoundManager::getManager()->play("selectPlayer.wav");
    irr::gui::IGUIImage *img = m_manager.GetEnv()->addImage(
            irr::core::rect<irr::s32>(0, 0, IrrlichtController::width, IrrlichtController::height),
            nullptr, UIElement::SPLASH_BACKGROUND,  L"", true);

    img->setImage(IrrlichtController::getDevice()->getVideoDriver()->getTexture(
            BomberManTexture::getModel("playerSelection").texture.c_str()));
    img->setScaleImage(true);
    m_boxContainer = new PlayerSelectionBoxContainer(&m_manager);
    /*new KeySelectionBox(&m_manager, irr::core::rect<irr::s32>(50, 50, IrrlichtController::width * 0.5, IrrlichtController::height * 0.5),
                        UIElement::MAP_SELECTION, 1);*/
}

void UIEventReceiver::DisplayGameOver() const
{

}


// Splash screen waiting for player to press some button
void UIEventReceiver::DisplaySplashScreen()
{
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
    std::cout << "Select Your Map" << std::endl;
    SoundManager::getManager()->play("selectMap.wav");
    irr::gui::IGUIListBox *listBox = m_manager.GetEnv()->addListBox(irr::core::rect<irr::s32>(IrrlichtController::width * 0.7, IrrlichtController::height * 0.1,
                                                             IrrlichtController::width * 0.95, IrrlichtController::height * 0.9), nullptr, UIElement::MAP_SELECTION, true);
    m_manager.GetEnv()->setFocus(listBox);
    listBox->setSelected(listBox->addItem(L"Map 1"));

    // Looks for saved games
    DIR *dir = opendir("tmpSaveMap");
    if (dir != nullptr)
    {
        for (dirent *files = readdir(dir); files != NULL; files = readdir(dir))
        {
            if (files->d_type == 8)
            {
                listBox->addItem(GameManager::ToWstring(std::string(files->d_name)).c_str());
            }
        }
    }
    closedir(dir);

    // Creates default map
    if (!m_spawned)
    {
        m_spawned = true;
        BomberMap::deleteMap();
        BomberMap::newMap("./media/smallMap/map1.xml");
        BomberMap::getMap()->genMap();
    }
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

/*
 * \brief Handles key Input events
 */
UIEventReceiver::EVENT_STATE UIEventReceiver::OnKeyInput(const irr::SEvent &event_copy)
{
    if (event_copy.EventType == irr::EET_KEY_INPUT_EVENT)
    {
        switch (event_copy.KeyInput.Key)
        {
            case irr::KEY_ESCAPE:
                // Unpause the game if in pause state
                if (GameManager::SharedInstance()->getGameState() == GameManager::PAUSE)
                {
                    GameManager::SharedInstance()->setGameState(GameManager::PLAY);
                    IrrlichtController::getDevice()->setEventReceiver(GameManager::SharedInstance()->getEventGame());
                    fptr = &UIEventReceiver::DisplayGameHUD;
                }
                // Quits the game otherwise
                else
                {
                    IrrlichtController::getDevice()->closeDevice();
                }
                break;

            case irr::KEY_RETURN:
                // Enters the main menu
                if (GameManager::SharedInstance()->getGameState() == GameManager::SPLASH_SCREEN &&
                    event_copy.KeyInput.PressedDown)
                {
                    GameManager::SharedInstance()->setGameState(GameManager::MAIN_MENU);
                    fptr = &UIEventReceiver::DisplayMainMenu;
                    return HANDELD;
                }
                break;

            case irr::KEY_SPACE:
                // Player 1 joined
                if (m_boxContainer != nullptr)
                {
                    m_boxContainer->PlayerJoin(1);
                    return HANDELD;
                }
                break;

            case irr::KEY_DOWN:
                if (event_copy.KeyInput.PressedDown)
                {
                    SelectNextButton();
                    if (m_boxContainer != nullptr)
                    {
                        m_boxContainer->SelectDown(1);
                    }
                }
                break;

            case irr::KEY_UP:
                if (event_copy.KeyInput.PressedDown)
                {
                    SelectPrevButton();
                    if (m_boxContainer != nullptr)
                    {
                        m_boxContainer->SelectUp(1);
                    }
                }
                break;

            case irr::KEY_LEFT:
                if (event_copy.KeyInput.PressedDown)
                {
                    if (m_boxContainer != nullptr)
                    {
                        m_boxContainer->SelectLeft(1);
                    }
                }
                break;

            case irr::KEY_RIGHT:
                if (event_copy.KeyInput.PressedDown)
                {
                    if (m_boxContainer != nullptr)
                    {
                        m_boxContainer->SelectRight(1);
                    }
                }
                break;

            default:
                break;
        }
    }
    return IGNORED;
}

UIEventReceiver::EVENT_STATE UIEventReceiver::OnGUIEvent(const irr::SEvent &event_copy)
{
    if (m_guiEvents.find(event_copy.GUIEvent.EventType) != m_guiEvents.end())
    {
        return (this->*m_guiEvents[event_copy.GUIEvent.EventType])(event_copy);
    }
    return NOT_HANDLED;
}

UIEventReceiver::EVENT_STATE UIEventReceiver::OnListBox(const irr::SEvent &event_copy)
{
    switch (event_copy.GUIEvent.EventType)
    {
        case irr::gui::EGET_LISTBOX_CHANGED:
        {
            irr::gui::IGUIListBox *listBox = (irr::gui::IGUIListBox *) event_copy.GUIEvent.Caller;
            BomberMap::deleteMap();
            if (GameManager::ToString(listBox->getListItem(listBox->getSelected())) == "Map 1")
            {
                BomberMap::newMap("./media/smallMap/map1.xml");
                BomberMap::getMap()->genMap();
            }
            else
            {
                GameManager::SharedInstance()->ClearPlayers();
                BomberMap::createMapFromSave(
                        "./tmpSaveMap/" + GameManager::ToString(listBox->getListItem(listBox->getSelected())));
            }
            break;
        }
        case irr::gui::EGET_LISTBOX_SELECTED_AGAIN:
        {
            irr::gui::IGUIListBox *listBox = (irr::gui::IGUIListBox *) event_copy.GUIEvent.Caller;
            // Empties the list of players if the map is a saved one
            if (GameManager::ToString(listBox->getListItem(listBox->getSelected())) == "Map 1")
            {
                GameManager::SharedInstance()->SwapCharacterList();
            }
            fptr = &UIEventReceiver::DisplayGameHUD;
            GameManager::SharedInstance()->setFptr(&GameManager::willStartGame);
            GameManager::SharedInstance()->setGameState(GameManager::PLAY);
            m_spawned = false;
            break;
        }

        default:
            break;
    }
    return IGNORED;
}

UIEventReceiver::EVENT_STATE UIEventReceiver::OnButtonClicked(const irr::SEvent &event_copy)
{
    irr::s32 id = event_copy.GUIEvent.Caller->getID();

    switch (id)
    {
        case UIElement::SPLASH_BUTTON_START:
            BomberMap::deleteMap();
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
            IrrlichtController::getDevice()->setEventReceiver(
                    GameManager::SharedInstance()->getEventGame());
            GameManager::SharedInstance()->setGameState(GameManager::PLAY);
            break;

        default:
            break;
    }
    return IGNORED;
}

UIEventReceiver::EVENT_STATE UIEventReceiver::OnElementFocused(const irr::SEvent &event_copy)
{
    //Permet de ne la load qu'au changement de state
    static int state = -1;
    irr::s32 id = event_copy.GUIEvent.Caller->getID();

    switch (id)
    {
        case UIElement::MAP_SELECTION1:
            if (state != 0)
            {
                std::cout << "SMALL" << std::endl;
                state = 0;
                BomberMap::deleteMap();
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
            return NOT_HANDLED;
            break;
    }

    return NOT_HANDLED;
}

void UIEventReceiver::HandleJoysticks(irr::SEvent const& event_copy)
{
    if (event_copy.EventType == irr::EET_JOYSTICK_INPUT_EVENT && m_joysticks[event_copy.JoystickEvent.Joystick])
    {
        m_joysticks[event_copy.JoystickEvent.Joystick]->setData(event_copy.JoystickEvent);
        long playerID = std::distance(m_joysticks.begin(), m_joysticks.find(event_copy.JoystickEvent.Joystick));

        // Validates on splash screen
        if (m_joysticks[event_copy.JoystickEvent.Joystick]->IsButtonPressed(MotionController::ControllerKey::CROSS))
        {
            if (GameManager::SharedInstance()->getGameState() == GameManager::SPLASH_SCREEN)
            {
                GameManager::SharedInstance()->setGameState(GameManager::MAIN_MENU);
                fptr = &UIEventReceiver::DisplayMainMenu;
            }
        }

        // Joins the party
        if (m_joysticks[event_copy.JoystickEvent.Joystick]->IsButtonPressed(MotionController::ControllerKey::CIRCLE))
        {
            if (m_boxContainer != nullptr)
            {
                m_boxContainer->PlayerJoin(playerID);
            }
        }

        // Navigates in menus
        if (m_joysticks[event_copy.JoystickEvent.Joystick]->getDirAxis(MotionController::LEFT_JOYSTICK) != ACharacter::IDLE)
        {
            if (m_boxContainer != nullptr)
            {
                ACharacter::ACTION act = m_joysticks[event_copy.JoystickEvent.Joystick]->getDirAxis(MotionController::LEFT_JOYSTICK);
                switch (act)
                {
                    case ACharacter::LEFT:
                        m_boxContainer->SelectLeft(playerID);
                        break;

                    case ACharacter::RIGHT:
                        m_boxContainer->SelectRight(playerID);
                        break;

                    case ACharacter::UP:
                        m_boxContainer->SelectUp(playerID);
                        break;

                    case ACharacter::DOWN:
                        m_boxContainer->SelectDown(playerID);
                        break;

                    default:
                        break;
                }
            }
        }
    }
}

