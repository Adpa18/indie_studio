//
// Created by gaspar_q on 4/27/16.
//

#include <irrlicht.h>
#include <AGameObject.hpp>
#include <Player.hpp>

int main()
{
    EventGame   eventGame;
    std::map<ACharacter::ACTION, irr::EKEY_CODE> keycodes;
    AGameObject *object = new Player("Richard", irr::core::vector3df(5, 0, 0), "../media/pikachu", 42, eventGame, keycodes);
    irr::IrrlichtDevice *device = IrrlichtController::getDevice();
    irr::scene::ISceneManager *manager = IrrlichtController::getSceneManager();
    irr::video::IVideoDriver *driver = IrrlichtController::getDriver();
    irr::scene::ICameraSceneNode* camera = IrrlichtController::getSceneManager()->addCameraSceneNode(0, irr::core::vector3df(0, 320, -250), irr::core::vector3df(0,5,0));

    while (device->run())
    {
        if (device->isWindowActive())
        {
            driver->beginScene(true, true, irr::video::SColor(255,200,200,200));
            manager->drawAll();
            driver->endScene();
        }
        else
            device->yield();
    }

    return (0);
}
