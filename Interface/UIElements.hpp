//
// Created by veyrie_f on 4/27/16.
//

#ifndef CPP_INDIE_STUDIO_UIELEMENTS_HPP
#define CPP_INDIE_STUDIO_UIELEMENTS_HPP

// TODO: video playback handler

// Holds all the element enum for the window
namespace UIElement
{
    // Objects for main menu
    enum MainMenu
    {
        MAIN_MENU_BUTTON_1P = 100,
        MAIN_MENU_BUTTON_2P,
        MAIN_MENU_BUTTON_3P,
        MAIN_MENU_BUTTON_4P
    };

    enum SplashScreen
    {
        SPLASH_BUTTON_START = 1
    };

    enum MapMenu
    {
        MAP_SELECTION1 = 200,
        MAP_SELECTION2,
        MAP_SELECTION3
    };

    enum PauseMenu
    {
        QUIT_BUTTON = 300,
        RESUME_BUTTON
    };
}

#endif //CPP_INDIE_STUDIO_UIELEMENTS_HPP
