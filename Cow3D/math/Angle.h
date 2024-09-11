#ifndef COW3D_ANGLE_H
#define COW3D_ANGLE_H

#include <cmath>

namespace cow {
class Angle {
public:
    static float radToDeg(float x) {
        return ((x) * 180.f / M_PI);
    }

    static float degToRad(float x) {
        return ((x) * M_PI / 180.f);
    }

};

}

#endif //COW3D_ANGLE_H
