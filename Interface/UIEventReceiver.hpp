//
// Created by veyrie_f on 4/27/16.
//

#ifndef CPP_INDIE_STUDIO_UIEVENTRECEIVER_HPP
#define CPP_INDIE_STUDIO_UIEVENTRECEIVER_HPP

#include <iostream>
#include <vector>
#include <list>
#include "../Irrlicht/irrlicht-1.8.3/include/irrlicht.h"
#include "UIElements.hpp"
#include "UIManager.hpp"
#include "PlayerSelectionBox.hpp"
#include "PlayerSelectionBoxContainer.hpp"

// Event receiver for ui
class UIEventReceiver : public irr::IEventReceiver
{
    // TODO: move this to game manager
    // enum GameState
    // {
    //     SPLASH_SCREEN = 1,
    //     MAIN_MENU = 2,
    //     MENU_MAP = 3,
    //     LOADING_SCREEN = 4,
    //     PLAY = 5,
    //     PAUSE
    // };

public:
    UIEventReceiver(UIManager const& manager);

public:
    virtual bool OnEvent(const irr::SEvent &event);

public:
  void DisplayPauseMenu();

private:
    void DisplayMainMenu();
    void DisplaySplashScreen();
    void DisplayMapMenu();
    void DisplayLoadingScreen();
  void DisplayGameHUD();

    /*
     * \brief Button handling
     */
    void RefreshButtons();
    void SelectNextButton();
    void SelectPrevButton();

    void LoadTextures();

private:
    UIManager m_manager;
    irr::IrrlichtDevice *m_device;

    // Use to know current game state and previous one
    // GameState m_gameState;
    // GameState m_gameSatePrev;

    void (UIEventReceiver::*fptr)() = nullptr;
    std::list<irr::gui::IGUIButton*> m_buttons;
    PlayerSelectionBoxContainer *m_boxContainer = nullptr;
};


#endif //CPP_INDIE_STUDIO_UIEVENTRECEIVER_HPP
