#ifndef COW3D_AUDIO_H
#define COW3D_AUDIO_H

#include <SDL3/SDL.h>
#include "Sound.h"

namespace cow {

class Audio {

public:

    Audio();

    void playSound(Sound *sound);

private:
    SDL_AudioStream *mStream;
    SDL_AudioSpec mSpec{};


};


}

#endif //COW3D_AUDIO_H
