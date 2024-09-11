#include "Cow3D.h"
#include "render/GlLoader.h"
#include "render/shader/DefaultShader.h"

namespace cow {

Cow3D::Cow3D(const std::string &windowName) : mWindow(windowName), mCamera() {

    mCamera.setPosition(Vec3f());
    mCamera.setLookAt(Vec3f(0, 0, 1));
    mCamera.setFov(80);
    mCamera.setViewport(Vec2f(800, 600));
    mCamera.setZoom(1);
}

bool Cow3D::pollEvent(SDL_Event &event) {
    return SDL_PollEvent(&event);
}

void Cow3D::update() {
    auto windowSize = mWindow.getSize();
    mCamera.setViewport(windowSize.to<float>());
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glViewport(0, 0, windowSize.x, windowSize.y);
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mScene3D.draw(mCamera);

    glDisable(GL_DEPTH_TEST);
    mScene2D.draw(mCamera);

    mWindow.swap();
}

}