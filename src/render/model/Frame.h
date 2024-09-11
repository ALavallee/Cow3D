#ifndef EVOCLIENT_FRAME_H
#define EVOCLIENT_FRAME_H

#include "math/Vec3.h"
#include "math/Quat.h"

template<class T>
struct Frame {
    float time;
    T v;
};

#endif //EVOCLIENT_FRAME_H
