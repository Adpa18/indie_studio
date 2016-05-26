//
// Created by wery_a on 26/05/16.
//

#include <stdexcept>
#include <fmod_errors.h>
#include "SoundManager.hpp"

FMOD::System             *SoundManager::engine = nullptr;
const std::string       SoundManager::soundPath = "./media/sound/";

FMOD::System  *SoundManager::getEngine()
{
    if (!engine)
    {
        FMOD::System_Create(&engine);
        engine->init(32, FMOD_INIT_NORMAL, NULL);
    }
    return (engine);
}

void    SoundManager::play(std::string const &sound_str, bool loop)
{
    FMOD::Sound *sound;

    getEngine()->createSound((soundPath + sound_str).c_str(), (loop) ? FMOD_LOOP_NORMAL : FMOD_DEFAULT, 0, &sound);
    engine->playSound(sound, 0, false, NULL);
}

void    SoundManager::stopAll()
{
//    getEngine()->stopAllSounds();
}