#ifndef EVOCLIENT_TIMEUTIL_H
#define EVOCLIENT_TIMEUTIL_H

#include <chrono>
#include <SDL3/SDL.h>

class TimeUtil {
public:

    static float getCurrentTimeInSeconds() {
        return static_cast<float>(SDL_GetTicks()) / 1000.f;
    }

};

#endif //EVOCLIENT_TIMEUTIL_H
