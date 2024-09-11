#ifndef EVO_VEC2_H
#define EVO_VEC2_H

#include <string>
#include <cmath>
#include "misc/data/ByteReader.h"

namespace cow {

template<class T>
class Vec2 {
public:

    Vec2() : x(0), y(0) {

    }

    Vec2(T x, T y) : x(x), y(y) {

    }

    Vec2 operator+(const Vec2 &rhs) const {
        return Vec2(x + rhs.x, y + rhs.y);
    }

    Vec2 operator-(const Vec2 &rhs) const {
        return Vec2(x - rhs.x, y - rhs.y);
    }

    Vec2 operator*(const Vec2 &rhs) const {
        return Vec2(x * rhs.x, y * rhs.y);
    }

    Vec2 operator*(const float rhs) const {
        return Vec2(x * rhs, y * rhs);
    }

    Vec2 operator/(const Vec2 &rhs) const {
        return Vec2(x / rhs.x, y / rhs.y);
    }

    Vec2 operator/(const T scalar) const {
        return Vec2(x / scalar, y / scalar);
    }

    bool operator==(const Vec2 &rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    bool equals(const Vec2 &rhs, T epsilon) const {
        return (std::abs(x - rhs.x) < epsilon) &&
               (std::abs(y - rhs.y) < epsilon);
    }

    template<class A>
    Vec2<A> to() {
        return Vec2<A>(static_cast<A>(x), static_cast<A>(y));
    }

    void read(ByteReader &reader) {
        x = reader.read<T>();
        y = reader.read<T>();
    }

    std::string toStr() const {
        return "( " + std::to_string(x) + " ," + std::to_string(y) + " )";
    }

    T x;
    T y;

};

typedef Vec2<int> Vec2i;
typedef Vec2<float> Vec2f;
typedef Vec2<double> Vec2d;
}

#include <unordered_map>

namespace std {
template<>
struct hash<cow::Vec2i> {
    size_t operator()(const cow::Vec2i &v) const {
        // A simple hash function combining the components of Vec2i
        return std::hash<int>()(v.x) ^ std::hash<int>()(v.y);
    }
};
}

#endif //EVO_VEC2_H
