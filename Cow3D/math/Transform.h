#ifndef COW3D_TRANSFORM_H
#define COW3D_TRANSFORM_H

#include "Mat4.h"
#include "Vec3.h"
#include "Quat.h"

namespace cow {

struct Transform {

    Vec3f translation;
    Quat rotation;
    Vec3f scale;

    static Transform Default() {
        Transform transform;
        transform.translation = Vec3f();
        transform.rotation = Quat::identity();
        transform.scale = Vec3f(1);
        return transform;
    }

    Mat4 toMat() {
        Mat4 result = Mat4::identity();

        Mat4 scaleMat = Mat4::fromScale(scale);
        Mat4 rotMat = Mat4::fromRotation(rotation);
        Mat4 transMat = Mat4::fromTranslation(translation);


        result = scaleMat * result;
        result = rotMat * result;
        result = transMat * result;

        return result;
    }

};

}

#endif //COW3D_TRANSFORM_H
