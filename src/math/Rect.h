#ifndef EVOCLIENT_RECT_H
#define EVOCLIENT_RECT_H

#include "Vec2.h"
#include "misc/data/ByteReader.h"

namespace cow {

template<class T>
class Rect {
public:

    Rect() = default;

    Rect(T x, T y, T w, T h) : pos(x, y), size(w, h) {

    }

    Rect(Vec2<T> pos, Vec2<T> size) : pos(pos), size(size) {

    }

    Vec2<T> getMin() {
        return pos - size;
    }

    Vec2<T> getMax() {
        return pos + size;
    }

    bool collides(Vec2<T> point) {
        Vec2<T> min = getMin();
        Vec2<T> max = getMax();

        return (point.x >= min.x && point.x <= max.x &&
                point.y >= min.y && point.y <= max.y);
    }


    Vec2<T> pos;
    Vec2<T> size;

};

typedef Rect<int> Recti;
typedef Rect<float> Rectf;

}

#endif //EVOCLIENT_RECT_H
