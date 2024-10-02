#include "Scene2D.h"
#include "Cow3D/render/shader/DefaultShader.h"

namespace cow {

Scene2D::Scene2D() {
    mScreenShader.loadFromSource(std::string(DefaultShader::ScreenVertex),
                                 std::string(DefaultShader::ScreenFragment));
}

Text *Scene2D::addText(Vec2f pos, std::string text, float fontSize) {
    auto newText = new Text(text, fontSize);
    newText->setPosition(pos);
    mTexts.push_back(newText);
    return newText;
}

Sprite *Scene2D::addSprite(cow::Vec2f pos, cow::Vec2f size, cow::Texture *texture) {
    auto newSprite = new Sprite(texture, size);
    newSprite->setPosition(pos);
    mSprites.push_back(newSprite);
    return newSprite;
}

void Scene2D::draw(Camera &camera) {
    mScreenShader.use();
    mScreenShader.setUniformMat4("camera", camera.getOrtho());
    for (auto &text: mTexts) {
        text->getFont()->getTexture().use();
        mScreenShader.setUniformVec4("color", text->getColor().toVec());
        mScreenShader.setUniformVec2("pos", text->getPosition());
        text->getVa().draw();
    }

    for (auto &sprite: mSprites) {
        sprite->getTexture()->use();
        mScreenShader.setUniformVec4("color", sprite->getColor().toVec());
        mScreenShader.setUniformVec2("pos", sprite->getPosition());
        auto size = sprite->getSize();
        VertexArray va({Vec2f()});
        return va;
    }
}

}