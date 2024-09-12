#ifndef COW3D_FRAME_H
#define COW3D_FRAME_H

#include "Cow3D/math/Vec3.h"
#include "Cow3D/math/Quat.h"

template<class T>
struct Frame {
    float time;
    T v;
};

#endif //COW3D_FRAME_H
