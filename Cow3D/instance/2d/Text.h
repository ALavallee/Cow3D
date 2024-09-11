#ifndef COW3D_TEXT_H
#define COW3D_TEXT_H

#include <string>
#include "Instance2D.h"
#include "render/Font.h"
#include "render/VertexArray.h"

namespace cow {

enum class TextAlign {
    Left = 1,
    Center = 2,
    Right = 3,
};

class Text : public Instance2D {

public:

    explicit Text(std::string text, float fontSize);

    const std::string &getText() {
        return mText;
    }

    VertexArray &getVa() {
        return mVa;
    }

    void setColor(Color color) {
        mColor = color;
    }

    Color getColor() {
        return mColor;
    }

    Font *getFont() const {
        return mFont;
    }

    float getFontSize() const {
        return mFontSize;
    }

private:

    Vec2f computeTextSize();

    void setupBuffer();

    std::string mText;
    TextAlign mAlign;
    Color mColor;
    float mFontSize;
    Font *mFont;
    VertexArray mVa;
};

}

#endif //COW3D_TEXT_H
