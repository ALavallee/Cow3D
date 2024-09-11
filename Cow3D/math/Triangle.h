#ifndef COW3D_TRIANGLE_H
#define COW3D_TRIANGLE_H

#include "Vec3.h"

namespace cow {

class Triangle {

public:
    Triangle() = default;

    Triangle(Vec3d p0, Vec3d p1, Vec3d p2) : p0(p0), p1(p1), p2(p2) {

    }

    Vec3d p0;
    Vec3d p1;
    Vec3d p2;


};

}

#endif //COW3D_TRIANGLE_H
