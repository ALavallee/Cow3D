#ifndef EVOCLIENT_TIMEUTIL_H
#define EVOCLIENT_TIMEUTIL_H

#include <chrono>
#include <SDL.h>

class TimeUtil {
public:

    static float getCurrentTimeInSeconds() {
        return static_cast<float>(SDL_GetTicks64()) / 1000.f;
    }

};

#endif //EVOCLIENT_TIMEUTIL_H
