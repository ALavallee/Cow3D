#ifndef EVO_MAT4_H
#define EVO_MAT4_H

#include "Vec3.h"
#include "Quat.h"

namespace cow {

class Mat4 {

public:

    static constexpr int Dim = 4;

    static Mat4 identity() {
        Mat4 result;
        result.set(0, 0, 1);
        result.set(1, 1, 1);
        result.set(2, 2, 1);
        result.set(3, 3, 1);
        return result;
    }

    static Mat4 fromTranslation(Vec3f translation) {
        Mat4 result = Mat4::identity();
        result.m[3][0] = translation.x;
        result.m[3][1] = translation.y;
        result.m[3][2] = translation.z;
        return result;
    }

    static Mat4 fromScale(Vec3f scale) {
        Mat4 result = Mat4::identity();
        result[0][0] = scale.x;
        result[1][1] = scale.y;
        result[2][2] = scale.z;
        return result;
    }

    static Mat4 fromRotation(Quat q) {
        Mat4 dest = Mat4::identity();
        float w, x, y, z,
                xx, yy, zz,
                xy, yz, xz,
                wx, wy, wz, norm, s;

        norm = q.norm();
        s = norm > 0.0f ? 2.0f / norm : 0.0f;

        x = q.x;
        y = q.y;
        z = q.z;
        w = q.w;

        xx = s * x * x;
        xy = s * x * y;
        wx = s * w * x;
        yy = s * y * y;
        yz = s * y * z;
        wy = s * w * y;
        zz = s * z * z;
        xz = s * x * z;
        wz = s * w * z;

        dest[0][0] = 1.0f - yy - zz;
        dest[1][1] = 1.0f - xx - zz;
        dest[2][2] = 1.0f - xx - yy;

        dest[0][1] = xy + wz;
        dest[1][2] = yz + wx;
        dest[2][0] = xz + wy;

        dest[1][0] = xy - wz;
        dest[2][1] = yz - wx;
        dest[0][2] = xz - wy;

        dest[0][3] = 0.0f;
        dest[1][3] = 0.0f;
        dest[2][3] = 0.0f;
        dest[3][0] = 0.0f;
        dest[3][1] = 0.0f;
        dest[3][2] = 0.0f;
        dest[3][3] = 1.0f;
        return dest;
    }

    Mat4() {
        for (auto &x: m) {
            for (float &y: x) {
                y = 0;
            }
        }
    }


    Mat4(float m00, float m01, float m02, float m03,
         float m10, float m11, float m12, float m13,
         float m20, float m21, float m22, float m23,
         float m30, float m31, float m32, float m33) {
        m[0][0] = m00;
        m[0][1] = m01;
        m[0][2] = m02;
        m[0][3] = m03;
        m[1][0] = m10;
        m[1][1] = m11;
        m[1][2] = m12;
        m[1][3] = m13;
        m[2][0] = m20;
        m[2][1] = m21;
        m[2][2] = m22;
        m[2][3] = m23;
        m[3][0] = m30;
        m[3][1] = m31;
        m[3][2] = m32;
        m[3][3] = m33;
    }


    void set(int x, int y, float value) {
        m[x][y] = value;
    }

    float get(int x, int y) {
        return m[x][y];
    }

    Mat4 operator*(const Mat4 &other) const {
        Mat4 dest;
        float a00 = m[0][0], a01 = m[0][1], a02 = m[0][2], a03 = m[0][3],
                a10 = m[1][0], a11 = m[1][1], a12 = m[1][2], a13 = m[1][3],
                a20 = m[2][0], a21 = m[2][1], a22 = m[2][2], a23 = m[2][3],
                a30 = m[3][0], a31 = m[3][1], a32 = m[3][2], a33 = m[3][3],

                b00 = other.m[0][0], b01 = other.m[0][1], b02 = other.m[0][2], b03 = other.m[0][3],
                b10 = other.m[1][0], b11 = other.m[1][1], b12 = other.m[1][2], b13 = other.m[1][3],
                b20 = other.m[2][0], b21 = other.m[2][1], b22 = other.m[2][2], b23 = other.m[2][3],
                b30 = other.m[3][0], b31 = other.m[3][1], b32 = other.m[3][2], b33 = other.m[3][3];

        dest.m[0][0] = a00 * b00 + a10 * b01 + a20 * b02 + a30 * b03;
        dest.m[0][1] = a01 * b00 + a11 * b01 + a21 * b02 + a31 * b03;
        dest.m[0][2] = a02 * b00 + a12 * b01 + a22 * b02 + a32 * b03;
        dest.m[0][3] = a03 * b00 + a13 * b01 + a23 * b02 + a33 * b03;
        dest.m[1][0] = a00 * b10 + a10 * b11 + a20 * b12 + a30 * b13;
        dest.m[1][1] = a01 * b10 + a11 * b11 + a21 * b12 + a31 * b13;
        dest.m[1][2] = a02 * b10 + a12 * b11 + a22 * b12 + a32 * b13;
        dest.m[1][3] = a03 * b10 + a13 * b11 + a23 * b12 + a33 * b13;
        dest.m[2][0] = a00 * b20 + a10 * b21 + a20 * b22 + a30 * b23;
        dest.m[2][1] = a01 * b20 + a11 * b21 + a21 * b22 + a31 * b23;
        dest.m[2][2] = a02 * b20 + a12 * b21 + a22 * b22 + a32 * b23;
        dest.m[2][3] = a03 * b20 + a13 * b21 + a23 * b22 + a33 * b23;
        dest.m[3][0] = a00 * b30 + a10 * b31 + a20 * b32 + a30 * b33;
        dest.m[3][1] = a01 * b30 + a11 * b31 + a21 * b32 + a31 * b33;
        dest.m[3][2] = a02 * b30 + a12 * b31 + a22 * b32 + a32 * b33;
        dest.m[3][3] = a03 * b30 + a13 * b31 + a23 * b32 + a33 * b33;
        return dest;
    }

    float (&operator[](int index))[Dim] {
        return m[index];
    }

    // Const overload for operator[] to work with const Mat4 objects
    const float (&operator[](int index) const )[Dim] {
        return m[index];
    }

    float determinant3x3(const float subMat[3][3]) const {
        return subMat[0][0] * (subMat[1][1] * subMat[2][2] - subMat[2][1] * subMat[1][2]) -
               subMat[0][1] * (subMat[1][0] * subMat[2][2] - subMat[1][2] * subMat[2][0]) +
               subMat[0][2] * (subMat[1][0] * subMat[2][1] - subMat[1][1] * subMat[2][0]);
    }

    float cofactor(int row, int col) const {
        float subMat[3][3];
        for (int i = 0, subI = 0; i < 4; ++i) {
            if (i == row) continue;
            for (int j = 0, subJ = 0; j < 4; ++j) {
                if (j == col) continue;
                subMat[subI][subJ] = m[i][j];
                ++subJ;
            }
            ++subI;
        }
        return determinant3x3(subMat);
    }


    float determinant() const {
        float det = 0.0f;
        for (int i = 0; i < 4; ++i) {
            det += (i % 2 == 0 ? 1.f : -1.f) * m[0][i] * cofactor(0, i);
        }
        return det;
    }

    Mat4 adjugate() const {
        Mat4 adj;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                // Note the transposition here: we use j, i instead of i, j
                adj.set(j, i, ((i + j) % 2 == 0 ? 1.f : -1.f) * cofactor(i, j));
            }
        }
        return adj;
    }

    Mat4 inverse() const {
        float det = determinant();
        Mat4 adj = adjugate();
        Mat4 inv;
        for (int i = 0; i < Dim; ++i) {
            for (int j = 0; j < Dim; ++j) {
                inv.set(i, j, adj[i][j] / det);
            }
        }
        return inv;
    }

private:
    float m[Dim][Dim]{};


};

}

#endif //EVO_MAT4_H
