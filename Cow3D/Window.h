#ifndef COW3D_WINDOW_H
#define COW3D_WINDOW_H

#include <string>
#include <SDL3/SDL.h>
#include "Cow3D/math/Vec2.h"

namespace cow {

class Window {

public:

    explicit Window(const std::string &windowName);

    void flipFullscreen();

    Vec2i getSize();

    void swap();

    void setMouseRelative(bool relative);

    void setHiddenMouse(bool hidden);

private:
    SDL_Window *mWindow;
    SDL_GLContext mContext;

};

}

#endif //COW3D_WINDOW_H
