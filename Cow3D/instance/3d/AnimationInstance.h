#ifndef COW3D_ANIMATIONINSTANCE_H
#define COW3D_ANIMATIONINSTANCE_H

#include "Instance3D.h"
#include "render/AnimatedModel.h"

namespace cow {

class AnimationInstance : public Instance3D {

public:

    explicit AnimationInstance(Model *model, float yScale) : mAnimatedModel(model), mYScale(yScale) {

    }

    void update() {
        mAnimatedModel.update();
    }

    AnimatedModel &getModel() {
        return mAnimatedModel;
    }

    void setYScale(float yScale) {
        mYScale = yScale;
    }

    float getYScale() {
        return mYScale;
    }


private:
    AnimatedModel mAnimatedModel;
    float mYScale;

};


}

#endif //COW3D_ANIMATIONINSTANCE_H
