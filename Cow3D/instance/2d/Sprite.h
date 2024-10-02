#ifndef COW3D_SPRITE_H
#define COW3D_SPRITE_H

#include "Text.h"

namespace cow {

class Sprite : public Instance2D {

public:

    Sprite(Texture *texture, Vec2f size) : mTexture(texture), mSize(size), mColor(Color::white()) {
    }

    Texture *getTexture() {
        return mTexture;
    }

    Vec2f getSize() {
        return mSize;
    }

    Color getColor() {
        return mColor;
    }

private:

    Texture *mTexture;
    Vec2f mSize;
    Color mColor;


};

}

#endif //COW3D_SPRITE_H
