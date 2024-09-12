#ifndef COW3D_INSTANCE2D_H
#define COW3D_INSTANCE2D_H

#include "Cow3D/math/Vec2.h"
#include "Cow3D/instance/Instance.h"

namespace cow {

class Instance2D : public Instance {


public:

    void setPosition(Vec2f pos) {
        mPosition = pos;
    }

    Vec2f getPosition() {
        return mPosition;
    }

private:

    Vec2f mPosition;

};

}

#endif //COW3D_INSTANCE2D_H
