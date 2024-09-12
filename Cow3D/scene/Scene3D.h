#ifndef COW3D_SCENE3D_H
#define COW3D_SCENE3D_H

#include <vector>
#include "Scene.h"
#include "Cow3D/math/Camera.h"
#include "Cow3D/render/VertexArray.h"
#include "Cow3D/instance/3d/Geometry.h"
#include "Cow3D/instance/3d/ModelInstance.h"
#include "Cow3D/instance/3d/AnimationInstance.h"
#include "Cow3D/render/shader/Shader.h"

namespace cow {

class Scene3D : public Scene {

public:

    Scene3D();

    AnimationInstance *addAnimation(Vec3f pos, Model *model, float yScale);

    ModelInstance *addModel(Vec3f pos, Model *model, float yScale);

    Geometry *addGeometry(Vec3f pos, std::vector<Vertex3D> &vertices);

    Geometry *addGeometry(Vec3f pos, std::vector<Vertex3DSimple> &vertices);

    void draw(Camera &camera);

private:
    Shader mGeoShader;
    Shader mModelShader;
    std::vector<Geometry *> mGeometries;
    std::vector<ModelInstance *> mModels;
    std::vector<AnimationInstance *> mAnimations;

};

}

#endif //COW3D_SCENE3D_H
