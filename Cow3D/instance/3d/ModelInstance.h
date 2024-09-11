#ifndef COW3D_MODELINSTANCE_H
#define COW3D_MODELINSTANCE_H

#include "render/model/Model.h"
#include "Instance3D.h"

namespace cow {

class ModelInstance : public Instance3D {

public:

    ModelInstance(Model *model, float yScale) : mModel(model), mYScale(yScale) {

    }

    float getYScale() {
        return mYScale;
    }

    Model *getModel() {
        return mModel;
    }


private:
    Model *mModel;
    float mYScale;


};


}


#endif //COW3D_MODELINSTANCE_H
