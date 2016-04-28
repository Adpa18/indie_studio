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
    // TODO: move this to game manager
    enum GameState
    {
        SPLASH_SCREEN = 1,
        MAIN_MENU = 2,
        MENU_MAP = 3,
        PLAY = 4,
        PAUSE
    };

public:
    UIEventReceiver(UIManager const& manager);

public:
    virtual bool OnEvent(const irr::SEvent &event);

private:
    void DisplayMainMenu();
    void DisplaySplashScreen();
    void DisplayMapMenu();

private:
    UIManager m_manager;
    irr::IrrlichtDevice *m_device;

    // Use to know current game state and previous one
    GameState m_gameState;
    GameState m_gameSatePrev;
};


#endif //CPP_INDIE_STUDIO_UIEVENTRECEIVER_HPP
