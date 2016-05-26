//
// Created by wery_a on 26/05/16.
//

#ifndef CPP_INDIE_STUDIO_SOUNDMANAGER_HPP
# define CPP_INDIE_STUDIO_SOUNDMANAGER_HPP

# include <string>
#include <fmod.hpp>

class SoundManager {
private:
    static FMOD::System         *engine;
    static const std::string    soundPath;

public:
    static FMOD::System             *getEngine();
    static void                     play(std::string const &sound_str, bool loop = false);
    static void                     stopAll();
};

#endif //CPP_INDIE_STUDIO_SOUNDMANAGER_HPP
