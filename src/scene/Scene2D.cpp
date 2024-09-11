#include "Scene2D.h"
#include "render/shader/DefaultShader.h"

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

void Scene2D::draw(Camera &camera) {
    mScreenShader.use();
    mScreenShader.setUniformMat4("camera", camera.getOrtho());
    for (auto &text: mTexts) {
        text->getFont()->getTexture().use();
        mScreenShader.setUniformVec4("color", text->getColor().toVec());
        text->getVa().draw();
    }
}

}