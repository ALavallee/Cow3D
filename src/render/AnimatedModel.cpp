#include "AnimatedModel.h"

namespace cow {

PlayingAnimation::PlayingAnimation(Model *model, Animation *animation, bool loop) : mModel(model),
                                                                                    mAnimation(animation), mLoop(loop),
                                                                                    mPlaybackTime(0) {
    mNodes = mModel->getNodes();
}

void PlayingAnimation::update(float time) {
    mPlaybackTime += time;

    // reset the nodes
    mNodes = mModel->getNodes();

    for (auto &track: mAnimation->tracks) {
        if (track.targetNodeId >= 0) {
            Node *target = &mNodes[track.targetNodeId];
            target->transform = track.sample(mPlaybackTime, mLoop, target->transform);
        }
    }
}

AnimatedModel::AnimatedModel(Model *model) : mModel(model) {

}

void AnimatedModel::update() {
    for (auto &animation: mPlaying) {
        animation.update(1.f / 144.f);
    }
}

bool AnimatedModel::playAnimation(std::string name, bool loop) {
    for (auto &animation: mModel->getAnimations()) {
        if (animation.name == name) {
            PlayingAnimation playingAnimation(mModel, &animation, loop);
            mPlaying.push_back(playingAnimation);
            return true;
        }
    }

    return false;
}

void AnimatedModel::playAnimation(size_t index, bool loop) {
    PlayingAnimation playingAnimation(mModel, &mModel->getAnimations()[index], loop);
    mPlaying.push_back(playingAnimation);
}

std::vector<Node> AnimatedModel::computeResultNodes() {

    for (auto &playing: mPlaying) {
        return playing.getNodes();
    }

    return mModel->getNodes();
}

Model *AnimatedModel::getModel() {
    return mModel;
}

}