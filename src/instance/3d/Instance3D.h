#ifndef COW3D_INSTANCE3D_H
#define COW3D_INSTANCE3D_H

#include "instance/Instance.h"
#include "math/vec3.h"

namespace cow {

class Instance3D : public Instance {


public:
    void setPosition(Vec3f position) {
        mPosition = position;
    }

    Vec3f getPosition() {
        return mPosition;
    }

private:
    Vec3f mPosition;

};

}

#endif //COW3D_INSTANCE3D_H
