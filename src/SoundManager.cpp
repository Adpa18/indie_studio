//
// Created by wery_a on 26/05/16.
//

#include <stdexcept>
#include <fmod_errors.h>
#include <vector>
#include <iostream>
#include "SoundManager.hpp"

SoundManager            *SoundManager::manager = NULL;

SoundManager            *SoundManager::getManager()
{
    if (!manager)
        manager = new SoundManager();
    return (manager);
}

SoundManager::SoundManager() : soundPath("./media/sound/")
{
    // FMOD::System_Create(&engine);
    // engine->init(32, FMOD_INIT_NORMAL, NULL);
}

SoundManager::~SoundManager()
{
    // for (std::map<std::string, FMOD::Sound *>::iterator it = this->_sounds.begin(); it != this->_sounds.end(); ++it)
    // {
    //     it->second->release();
    // }
    // engine->close();
    // engine->release();
}

void    SoundManager::play(std::string const &sound, unsigned int id, bool loop, float volume)
{
    // if (this->_sounds[sound] == 0)
    // {
    //     engine->createSound((soundPath + sound).c_str(), (loop) ? FMOD_LOOP_NORMAL : FMOD_DEFAULT, 0, &this->_sounds[sound]);
    // }
    // engine->playSound(this->_sounds[sound], 0, false, &this->_channels[id]);
    // this->_channels[id]->setVolume(volume);
}

void    SoundManager::stop(int id)
{
    // if (id == -1)
    //     stopAll();
    // this->_channels[id]->stop();
}

void    SoundManager::stopAll()
{
    // for (std::map<unsigned int, FMOD::Channel *>::iterator it = this->_channels.begin(); it != this->_channels.end(); ++it)
    // {
    //     it->second->stop();
    // }
}
