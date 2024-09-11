#ifndef COW3D_SOUND_H
#define COW3D_SOUND_H

#include <SDL3/SDL.h>
#include <string>
#include <vector>

namespace cow {

class Sound {

public:

    void load(const std::string &path);

    Uint8 *getBuffer() {
        return mSoundBuffer.data();
    }

    Uint32 getLength() {
        return mSoundLength;
    }

private:
    SDL_AudioSpec mSoundSpec;
    std::vector<unsigned char> mSoundBuffer;
    Uint32 mSoundLength;

};


}

#endif //COW3D_SOUND_H
