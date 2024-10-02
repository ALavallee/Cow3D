#ifndef COW3D_SCENE2D_H
#define COW3D_SCENE2D_H

#include <vector>
#include "Cow3D/instance/2d/Text.h"
#include "Cow3D/instance/2d/Sprite.h"
#include "Scene.h"
#include "Cow3D/render/shader/Shader.h"
#include "Cow3D/math/Camera.h"

namespace cow {

class Scene2D : public Scene {

public:

    Scene2D();

    Text *addText(Vec2f pos, std::string text, float fontSize);

    Sprite *addSprite(Vec2f pos, Vec2f size, Texture *texture);

    void draw(Camera &camera);

private:
    std::vector<Text *> mTexts;
    std::vector<Sprite *> mSprites;
    Shader mScreenShader;

};

}

#endif //COW3D_SCENE2D_H
