#include "Window.h"
#include "render/GlLoader.h"

namespace cow {

Window::Window(const std::string &windowName) {
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC |
             SDL_INIT_GAMEPAD | SDL_INIT_SENSOR | SDL_INIT_AUDIO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1); // Enable multisampling
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16); // Set number of samples
    mWindow = SDL_CreateWindow(windowName.c_str(), 800, 600, SDL_WINDOW_OPENGL);
    mContext = SDL_GL_CreateContext(mWindow);
    gl_load();
}

void Window::flipFullscreen() {
    Uint32 flags = SDL_GetWindowFlags(mWindow);
    if (flags & SDL_WINDOW_FULLSCREEN) {
        SDL_SetWindowFullscreen(mWindow, false);
    } else {
        SDL_SetWindowFullscreen(mWindow, true);
    }
}

Vec2i Window::getSize() {
    Vec2i size;
    SDL_GetWindowSize(mWindow, &size.x, &size.y);
    return size;
}

void Window::swap() {
    SDL_GL_SwapWindow(mWindow);
}

}