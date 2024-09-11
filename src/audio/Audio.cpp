#include "Audio.h"

namespace cow {


Audio::Audio() {
    mSpec.channels = 2;
    mSpec.format = SDL_AUDIO_F32;
    mSpec.freq = 48000;

    mStream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &mSpec, nullptr, nullptr);
    SDL_ResumeAudioStreamDevice(mStream);
}

void Audio::playSound(Sound *sound) {
    SDL_PutAudioStreamData(mStream, sound->getBuffer(), static_cast<int>(sound->getLength()));
}

}