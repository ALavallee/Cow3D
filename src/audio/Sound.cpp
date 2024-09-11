#include "Sound.h"

namespace cow {

void Sound::load(const std::string &path) {

    SDL_AudioSpec wavSpec;
    Uint8 *wavBuffer;
    Uint32 wavLength;
    SDL_LoadWAV(path.c_str(), &wavSpec, &wavBuffer, &wavLength);


    mSoundSpec.channels = 2;
    mSoundSpec.format = SDL_AUDIO_F32;
    mSoundSpec.freq = 48000;
    SDL_AudioStream *converter = SDL_CreateAudioStream(&wavSpec, &mSoundSpec);
    SDL_PutAudioStreamData(converter, wavBuffer, static_cast<int>(wavLength));
    SDL_free(wavBuffer);
    mSoundBuffer.resize(wavLength * 4);
    mSoundLength = SDL_GetAudioStreamData(converter, &mSoundBuffer[0], static_cast<int>(mSoundBuffer.size()));
    SDL_DestroyAudioStream(converter);
}


}