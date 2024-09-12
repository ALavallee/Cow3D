#ifndef COW3D_GEOMETRY_H
#define COW3D_GEOMETRY_H

#include <vector>
#include "Instance3D.h"
#include "Cow3D/render/VertexArray.h"
#include "Cow3D/render/Color.h"

namespace cow {


class Geometry : public Instance3D {

public:

    explicit Geometry(std::vector<Vertex3D> &vertices) : mVa(vertices), mColor(Color::white()) {
    }

    explicit Geometry(std::vector<Vertex3DSimple> &vertices) : mVa(vertices), mColor(Color::white()) {

    }

    void setColor(Color color) {
        mColor = color;
    }

    Color getColor() {
        return mColor;
    }

    VertexArray &getVa() {
        return mVa;
    }


private:

    Color mColor;
    VertexArray mVa;


};

}

#endif //COW3D_GEOMETRY_H
