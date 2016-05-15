//
// Created by veyrie_f on 4/27/16.
//

#include "UIManager.hpp"
#include "UIEventReceiver.hpp"
#include "../include/Texture.hpp"

int main()
{
    IrrlichtController::width = 1920;
    IrrlichtController::height = 1080;
    UIManager uiManager(IrrlichtController::getDevice(false));
    BomberManTexture::loadTexture();
    UIEventReceiver *uiEventReceiver = new UIEventReceiver(uiManager);

    IrrlichtController::getDevice()->setEventReceiver(uiEventReceiver);

    while (IrrlichtController::getDevice()->run() && IrrlichtController::getDriver())
    {
        if (IrrlichtController::getDevice()->isWindowActive())
        {
            IrrlichtController::getDriver()->beginScene(true, true, irr::video::SColor(0, 200, 200, 200));
            IrrlichtController::getDevice()->getVideoDriver()->setViewPort(irr::core::rect<irr::s32>(IrrlichtController::width * 0.014, IrrlichtController::height * 0.445,
                                                                                                     IrrlichtController::width * 0.24, IrrlichtController::height * 0.85));
            IrrlichtController::getDevice()->getSceneManager()->drawAll();
            IrrlichtController::getDevice()->getVideoDriver()->setViewPort(irr::core::rect<irr::s32>(0, 0,
                                                                                                     IrrlichtController::width, IrrlichtController::height));
            IrrlichtController::getDevice()->getGUIEnvironment()->drawAll();
            IrrlichtController::getDriver()->endScene();
        }
    }

    IrrlichtController::getDevice()->drop();
    return 0;
}