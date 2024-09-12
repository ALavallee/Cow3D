#ifndef COW3D_ANIMATED_MODEL_H
#define COW3D_ANIMATED_MODEL_H

#include <vector>
#include "Cow3D/render/model/Model.h"
#include "Cow3D/render/model/Model.h"

namespace cow {

class PlayingAnimation {

public:

    PlayingAnimation(Model *model, Animation *animation, bool loop);

    void update(float time);

    std::vector<Node> &getNodes() { return mNodes; }

private:
    Animation *mAnimation;
    Model *mModel;
    bool mLoop;
    float mPlaybackTime;
    std::vector<Node> mNodes;
};

class AnimatedModel {

public:

    explicit AnimatedModel(Model *model);

    void update();

    bool playAnimation(std::string name, bool loop);

    void playAnimation(size_t index, bool loop);

    std::vector<Node> computeResultNodes();

    Model *getModel();

private:

    Model *mModel;
    std::vector<PlayingAnimation> mPlaying;

};

}

#endif //COW3D_ANIMATED_MODEL_H
