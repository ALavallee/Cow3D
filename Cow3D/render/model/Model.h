#ifndef EVOCLIENT_MODEL_H
#define EVOCLIENT_MODEL_H

#include <vector>
#include "render/Texture.h"
#include "Mesh.h"
#include "Animation.h"
#include "Node.h"

namespace cow {

class Model {

public:

    Model();

    bool loadFromFile(std::string path);

    std::vector<Node> &getNodes() { return mNodes; }

    std::vector<Animation> &getAnimations() { return mAnimations; }

    Vec3f getMinPos();

    Vec3f getMaxPos();

    float getScalingFactorY(float y);

    size_t getMeshesCount();

    Mesh *getMesh(size_t i);

    Texture &getTexture();


private:
    Texture mTexture;
    std::vector<Mesh> mMeshes;
    std::vector<Node> mNodes;
    std::vector<Animation> mAnimations;
};

}

#endif //EVOCLIENT_MODEL_H
