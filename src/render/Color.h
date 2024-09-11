#ifndef EVOCLIENT_COLOR_H
#define EVOCLIENT_COLOR_H

#include "math/Vec4.h"

namespace cow {

class Color {
public:
    unsigned char r, g, b, a;

    static constexpr Color fromFloats(float r, float g, float b, float a = 1.0f) {
        return {static_cast<unsigned char>(r * 255),
                static_cast<unsigned char>(g * 255),
                static_cast<unsigned char>(b * 255),
                static_cast<unsigned char>(a * 255)};
    }


    constexpr Color() : r(0), g(0), b(0), a(255) {

    }

    constexpr Color(Color const &color) : Color(color.r, color.g, color.b, color.a) {
    }

    constexpr Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255) : r(r), g(g), b(b), a(a) {

    }

    Vec4f toVec() const {
        return {static_cast<float>(r) / 255.f,
                static_cast<float>(g) / 255.f,
                static_cast<float>(b) / 255.f,
                static_cast<float>(a) / 255.f};
    }

    static constexpr Color red() { return {255, 0, 0}; }

    static constexpr Color green() { return {0, 255, 0}; }

    static constexpr Color blue() { return {0, 0, 255}; }

    static constexpr Color white() { return {255, 255, 255}; }

    static constexpr Color black() { return {0, 0, 0}; }

    static constexpr Color yellow() { return {255, 255, 0}; }

    static constexpr Color cyan() { return {0, 255, 255}; }

    static constexpr Color magenta() { return {255, 0, 255}; }

    static constexpr Color transparent() { return {255, 255, 255, 0}; }

};

}

#endif //EVOCLIENT_COLOR_H
