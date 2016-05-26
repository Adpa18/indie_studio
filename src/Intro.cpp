//
// Created by wery_a on 26/05/16.
//

#include <dirent.h>
#include <algorithm>
#include <unistd.h>
#include <iostream>
#include "IrrlichtController.hpp"
#include "Intro.hpp"

const std::string     Intro::default_path_video = "./media/intro/video/";
const std::string     Intro::default_path_sound = "./media/intro/sound/";


Intro::Intro(EventGame *eventGame) : eventGame(eventGame)
{
    DIR	*rep;

    rep = opendir(default_path_video.data());
    if (rep != NULL)
    {
        struct dirent	*ent;

        while ((ent = readdir(rep)) != NULL)
        {
            if (std::string(ent->d_name) != "." && std::string(ent->d_name) != "..")
                this->files.push_back(default_path_video + std::string(ent->d_name));
        }
        closedir(rep);
        std::sort(this->files.begin(), this->files.end());
    }
}

Intro::~Intro()
{

}

void	Intro::run()
{
    irr::IrrlichtDevice* device = IrrlichtController::getDevice();
    irr::video::IVideoDriver* driver = device->getVideoDriver();
    irrklang::ISoundEngine *engine = IrrlichtController::getIrrKlangDevice();
    irr::gui::IGUIEnvironment *guiEnv = IrrlichtController::getGUIEnvironment();
    if (!device || !driver || !engine || !guiEnv || !eventGame) {
        return;
    }
    size_t  i = 0;
    clock_t	timerFrame;
    irr::gui::IGUIImage *img;
    img = guiEnv->addImage(irr::core::rect<irr::s32>(0,0, IrrlichtController::width, IrrlichtController::height));
    while (device->run() && i < this->files.size())
    {
        if (eventGame->IsKeyDownOneTime(irr::KEY_RETURN))
            break;

        if (i == 24)
            engine->play2D((default_path_sound + "intro.wav").c_str(), false);
        timerFrame = clock();
        irr::video::ITexture *tex = driver->getTexture((this->files[i]).c_str());
        img->setImage(tex);
        img->setScaleImage(true);
        driver->beginScene(true, true, irr::video::SColor(0,0,0,0));
        IrrlichtController::getGUIEnvironment()->drawAll();
        driver->endScene();
        driver->removeTexture(tex);
        timerFrame = clock() - timerFrame;
        if (static_cast<float>(timerFrame) / CLOCKS_PER_SEC < 1.0 / 23.975)
            usleep(1000000.0 / 23.975 - static_cast<float>(timerFrame) / CLOCKS_PER_SEC * 1000000.0);
        ++i;
    }
    engine->stopAllSounds();
}
