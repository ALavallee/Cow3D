#ifndef COW3D_COW3D_H
#define COW3D_COW3D_H

#include <SDL3/SDL.h>
#include <string>
#include "ResManager.h"
#include "math/Camera.h"
#include "render/shader/Shader.h"
#include "scene/Scene3D.h"
#include "scene/Scene2D.h"
#include "Window.h"
#include "audio/Audio.h"

namespace cow {

class Cow3D {

public:

    explicit Cow3D(const std::string &windowName);

    bool pollEvent(SDL_Event &event);

    void update();

    Audio &getAudio() {
        return mAudio;
    }

    Window &getWindow() {
        return mWindow;
    }

    Camera &getCamera() {
        return mCamera;
    }

    Scene3D &getScene3D() {
        return mScene3D;
    }

    Scene2D &getScene2D() {
        return mScene2D;
    }

    ResManager &getRes() {
        return mResManager;
    };

private:

    Window mWindow;
    ResManager mResManager;
    Audio mAudio;

    Camera mCamera;

    Scene3D mScene3D;
    Scene2D mScene2D;
};


}

#endif //COW3D_COW3D_H
