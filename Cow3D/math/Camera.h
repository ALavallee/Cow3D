#ifndef COW3D_CAMERA_H
#define COW3D_CAMERA_H

#include "Mat4.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Box.h"

namespace cow {

struct Plane {
    Vec3f normal;
    float distance;

    // Normalize the plane
    void normalize() {
        float mag = std::sqrt(normal.dot(normal));
        normal = normal / mag;
        distance /= mag;
    }

    // Check if a point is on the positive side of the plane
    bool isPointOnPositiveSide(const Vec3f &point) const {
        return normal.dot(point) + distance >= 0;
    }
};

class Camera {

public:
    Camera();

    Mat4 getProjection();

    Mat4 getView();

    Mat4 getOrtho();

    void setPosition(Vec3f pos) {
        mPos = pos;
    }

    Vec3f getPosition() {
        return mPos;
    }

    void setViewport(Vec2f viewport) {
        mViewport = viewport;
    }

    Vec2f getViewport() {
        return mViewport;
    }

    void setLookAt(Vec3f look) {
        mLookAt = look;
    }

    Vec3f getLookAt() {
        return mLookAt;
    }

    void setZoom(float zoom) {
        mZoom = zoom;
    }

    float getZoom() {
        return mZoom;
    }

    void setFov(float fov) {
        mFov = fov;
    }

    float getFov() {
        return mFov;
    }

    bool isBoxInFrustum(Boxf point) {
        return isBoxInFrustum(point.min(), point.max());
    }

private:

    bool isBoxInFrustum(const Vec3f &minPoint, const Vec3f &maxPoint);

    std::array<Plane, 6> extractFrustumPlanes(const Mat4 &viewProj);

    Vec3f mPos;
    Vec3f mLookAt;
    Vec2f mViewport;
    float mZoom;
    float mFov;
};

}

#endif //COW3D_CAMERA_H
