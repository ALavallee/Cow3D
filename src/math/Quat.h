#ifndef COW3D_QUAT_H
#define COW3D_QUAT_H

#include <cmath>

namespace cow {

struct Quat {

    float x, y, z, w;

    static Quat fromEuler(float xRad, float yRad, float zRad) {
        float cx = cosf(xRad * 0.5f);
        float sx = sinf(xRad * 0.5f);
        float cy = cosf(yRad * 0.5f);
        float sy = sinf(yRad * 0.5f);
        float cz = cosf(zRad * 0.5f);
        float sz = sinf(zRad * 0.5f);

        float qw = cx * cy * cz + sx * sy * sz;
        float qx = sx * cy * cz - cx * sy * sz;
        float qy = cx * sy * cz + sx * cy * sz;
        float qz = cx * cy * sz - sx * sy * cz;

        return {qx, qy, qz, qw};
    }

    static Quat fromEuler(Vec3f rad) {
        return fromEuler(rad.x, rad.y, rad.z);
    }

    static Quat identity() {
        return {0, 0, 0, 1};
    }

    Quat() : x(0), y(0), z(0), w(0) {

    }

    Quat(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {

    }

    Quat lerp(const Quat &end, float t) {
        Quat result;
        result.x = x + (end.x - x) * t;
        result.y = y + (end.y - y) * t;
        result.z = z + (end.z - z) * t;
        result.w = w + (end.w - w) * t;
        result.normalize();
        return result;
    }

    void normalize() {
        float len = sqrtf(x * x + y * y + z * z + w * w);
        if (len > 0) {
            x /= len;
            y /= len;
            z /= len;
            w /= len;
        }
    }

    float dot(const Quat &b) const {
        return x * b.x + y * b.y + z * b.z + w * b.w;
    }

    float norm() const {
        return sqrtf(dot(*this));
    }

    std::string toStr() {
        return "( " + std::to_string(x) + " , " + std::to_string(y) +
               " , " + std::to_string(z) + " , " + std::to_string(w) + " )";
    }

};

}

#endif //COW3D_QUAT_H
