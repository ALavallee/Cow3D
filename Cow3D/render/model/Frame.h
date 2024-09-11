#ifndef COW3D_FRAME_H
#define COW3D_FRAME_H

#include "math/Vec3.h"
#include "math/Quat.h"

template<class T>
struct Frame {
    float time;
    T v;
};

#endif //COW3D_FRAME_H
