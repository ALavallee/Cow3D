#ifndef COW3D_BOX_H
#define COW3D_BOX_H

#include "Vec3.h"
#include "misc/data/ByteReader.h"

namespace cow {

template<class T>
class Box {
public:

    Box() {

    }

    Box(Vec3<T> pos, Vec3<T> size) : pos(pos), size(size) {

    }

    void read(ByteReader &reader) {
        pos.read(reader);
        size.read(reader);
    }

    Vec3<T> min() {
        return pos - size;
    }

    Vec3<T> max() {
        return pos + size;
    }

    template<class C>
    Box<C> to() {
        Box<C> box;
        box.pos = pos.template to<C>();
        box.size = size.template to<C>();
        return box;
    }

    Vec3<T> pos;
    Vec3<T> size;

};

typedef Box<int> Boxi;
typedef Box<float> Boxf;
typedef Box<double> Boxd;

}

#endif //COW3D_BOX_H
