//
// Created by veyrie_f on 4/27/16.
//

#include "UIManager.hpp"
#include "UIEventReceiver.hpp"
#include "../include/Texture.hpp"

int main()
{
    IrrlichtController::width = 640;
    IrrlichtController::height = 640;
    UIManager uiManager(IrrlichtController::getDevice(false));
    BomberManTexture::loadTexture();
    UIEventReceiver *uiEventReceiver = new UIEventReceiver(uiManager);

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