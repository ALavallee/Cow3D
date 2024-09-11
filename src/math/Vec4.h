#ifndef EVO_VEC4_H
#define EVO_VEC4_H

namespace cow {

template<class T>
class Vec4 {

public:

    constexpr Vec4() : x(0), y(0), z(0), w(0) {

    }

    constexpr explicit Vec4(T v) : x(v), y(v), z(v), w(v) {

    }

    constexpr Vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {

    }

    T x, y, z, w;

};

typedef Vec4<int> Vec4i;
typedef Vec4<float> Vec4f;

}

#endif //FABLE_OF_OEMIA_VEC4_H
