#ifndef OECLIENT_TRIANGLE_H
#define OECLIENT_TRIANGLE_H

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

#endif //OECLIENT_TRIANGLE_H
