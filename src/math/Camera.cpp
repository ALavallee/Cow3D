#include "Camera.h"
#include <cmath>
#include "Angle.h"

namespace cow {

Camera::Camera() : mPos(), mLookAt(0, 0, 1), mViewport(800, 600), mZoom(1), mFov(70.f) {

}

Mat4 Camera::getProjection() {
    float aspectRatio = mViewport.x / mViewport.y;
    float nearPlane = 0.2f;
    float farPlane = 5000.0f;
    float fovRad = Angle::degToRad(mFov);

    Mat4 proj;
    proj[0][0] = fovRad / aspectRatio;
    proj[1][1] = fovRad;
    proj[2][2] = farPlane / (farPlane - nearPlane);
    proj[3][2] = (-farPlane * nearPlane) / (farPlane - nearPlane);
    proj[2][3] = 1.0f;
    proj[3][3] = 0.0f;

    return proj;
}

Mat4 Camera::getView() {
    Vec3f up(0.0f, 1.0f, 0.0f);

    Vec3f f = (mLookAt - mPos).normalize();
    Vec3f s = f.cross(up).normalize();
    Vec3f u = s.cross(f);

    Mat4 dest;
    dest[0][0] = s[0];
    dest[0][1] = u[0];
    dest[0][2] = f[0];
    dest[1][0] = s[1];
    dest[1][1] = u[1];
    dest[1][2] = f[1];
    dest[2][0] = s[2];
    dest[2][1] = u[2];
    dest[2][2] = f[2];
    dest[3][0] = -s.dot(mPos);
    dest[3][1] = -u.dot(mPos);
    dest[3][2] = -f.dot(mPos);
    dest[0][3] = dest[1][3] = dest[2][3] = 0.0f;
    dest[3][3] = 1.0f;
    return dest;
}

Mat4 Camera::getOrtho() {
    float left = -mViewport.x / 2.0f * mZoom;
    float right = mViewport.x / 2.0f * mZoom;
    float bottom = -mViewport.y / 2.0f * mZoom;
    float top = mViewport.y / 2.0f * mZoom;

    float nearPlane = -1.f;
    float farPlane = 1.f;

    Mat4 ortho;
    ortho[0][0] = 2.0f / (right - left);
    ortho[1][1] = 2.0f / (top - bottom);
    ortho[2][2] = -2.0f / (farPlane - nearPlane);
    ortho[3][0] = -(right + left) / (right - left);
    ortho[3][1] = -(top + bottom) / (top - bottom);
    ortho[3][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);
    ortho[3][3] = 1.0f;
    return ortho;
}

bool Camera::isBoxInFrustum(const Vec3f &minPoint, const Vec3f &maxPoint) {
    auto planes = extractFrustumPlanes(getProjection() * getView());
    for (const auto &plane: planes) {
        // Check all eight points of the box against this plane
        if (plane.isPointOnPositiveSide(Vec3f(minPoint.x, minPoint.y, minPoint.z)) ||
            plane.isPointOnPositiveSide(Vec3f(maxPoint.x, minPoint.y, minPoint.z)) ||
            plane.isPointOnPositiveSide(Vec3f(minPoint.x, maxPoint.y, minPoint.z)) ||
            plane.isPointOnPositiveSide(Vec3f(maxPoint.x, maxPoint.y, minPoint.z)) ||
            plane.isPointOnPositiveSide(Vec3f(minPoint.x, minPoint.y, maxPoint.z)) ||
            plane.isPointOnPositiveSide(Vec3f(maxPoint.x, minPoint.y, maxPoint.z)) ||
            plane.isPointOnPositiveSide(Vec3f(minPoint.x, maxPoint.y, maxPoint.z)) ||
            plane.isPointOnPositiveSide(Vec3f(maxPoint.x, maxPoint.y, maxPoint.z))) {
            continue; // Box is at least partially inside this plane
        }

        // If all points are outside this plane, the box is outside the frustum
        return false;
    }

    // If it passed all planes, it is inside the frustum
    return true;
}

std::array<Plane, 6> Camera::extractFrustumPlanes(const Mat4 &viewProj) {
    std::array<Plane, 6> planes;

    // Left
    planes[0].normal.x = viewProj[0][3] + viewProj[0][0];
    planes[0].normal.y = viewProj[1][3] + viewProj[1][0];
    planes[0].normal.z = viewProj[2][3] + viewProj[2][0];
    planes[0].distance = viewProj[3][3] + viewProj[3][0];

    // Right
    planes[1].normal.x = viewProj[0][3] - viewProj[0][0];
    planes[1].normal.y = viewProj[1][3] - viewProj[1][0];
    planes[1].normal.z = viewProj[2][3] - viewProj[2][0];
    planes[1].distance = viewProj[3][3] - viewProj[3][0];

    // Bottom
    planes[2].normal.x = viewProj[0][3] + viewProj[0][1];
    planes[2].normal.y = viewProj[1][3] + viewProj[1][1];
    planes[2].normal.z = viewProj[2][3] + viewProj[2][1];
    planes[2].distance = viewProj[3][3] + viewProj[3][1];

    // Top
    planes[3].normal.x = viewProj[0][3] - viewProj[0][1];
    planes[3].normal.y = viewProj[1][3] - viewProj[1][1];
    planes[3].normal.z = viewProj[2][3] - viewProj[2][1];
    planes[3].distance = viewProj[3][3] - viewProj[3][1];

    // Near
    planes[4].normal.x = viewProj[0][3] + viewProj[0][2];
    planes[4].normal.y = viewProj[1][3] + viewProj[1][2];
    planes[4].normal.z = viewProj[2][3] + viewProj[2][2];
    planes[4].distance = viewProj[3][3] + viewProj[3][2];

    // Far
    planes[5].normal.x = viewProj[0][3] - viewProj[0][2];
    planes[5].normal.y = viewProj[1][3] - viewProj[1][2];
    planes[5].normal.z = viewProj[2][3] - viewProj[2][2];
    planes[5].distance = viewProj[3][3] - viewProj[3][2];

    // Normalize all planes
    for (auto &plane: planes) {
        plane.normalize();
    }

    return planes;
}

}
