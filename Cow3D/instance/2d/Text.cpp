#include "Text.h"

namespace cow {

Text::Text(std::string text, float fontSize) : mText(text), mColor(Color::white()), mAlign(TextAlign::Center),
                                               mFontSize(fontSize), mFont(Font::Default()) {
    setupBuffer();
}

Vec2f Text::computeTextSize() {
    float totalWidth = 0.0f;
    float maxHeight = 0.0f;

    // Scale the font size relative to the default font size
    float scaleFactor = mFontSize / static_cast<float>(Font::DefaultFontSize);

    for (char c: mText) {
        Glyph glyph = mFont->getGlyph(c);

        if (c == ' ') {
            totalWidth += (Font::DefaultFontSize / 2.f) * scaleFactor; // Add space width
        } else {

            float scaledWidth = static_cast<float>(glyph.box.size.x) * scaleFactor;

            // Accumulate the total width
            totalWidth += scaledWidth;


            float scaledHeight = static_cast<float>(glyph.box.size.y) * scaleFactor;
            if (scaledHeight > maxHeight) {
                maxHeight = scaledHeight;
            }
        }
    }


    return {totalWidth, maxHeight};
}

void Text::setupBuffer() {
    auto computedSize = computeTextSize();
    Vec2f pos = getPosition();
    if (mAlign == TextAlign::Center) {
        pos.x -= computedSize.x / 2.f;
    } else if (mAlign == TextAlign::Right) {
        pos.x -= computedSize.x;
    }

    float fontSize = mFontSize / static_cast<float>(Font::DefaultFontSize);
    std::vector<Vertex2D> allPoints;

    float x = pos.x;
    float y = pos.y;

    for (char c: mText) {
        Glyph glyph = mFont->getGlyph(c);
        if (c == ' ') {
            x += (float) (Font::DefaultFontSize / 2.f) * fontSize;
        } else {

            // Compute texture coordinates
            float u0 = (float) glyph.box.pos.x / (float) mFont->getTexture().getWidth();
            float v0 = (float) glyph.box.pos.y / (float) mFont->getTexture().getHeight();
            float u1 = (float) (glyph.box.pos.x + glyph.box.size.x) / (float) mFont->getTexture().getWidth();
            float v1 = (float) (glyph.box.pos.y + glyph.box.size.y) / (float) mFont->getTexture().getHeight();

            // Compute screen coordinates and apply the font size scaling
            float scaledW = (float) glyph.box.size.x * fontSize;
            float scaledH = (float) glyph.box.size.y * fontSize;
            float x0 = x;
            float y0 = y;
            float x1 = x0 + scaledW;
            float y1 = y0 + scaledH;

            Vertex2D points[6] = {
                    Vertex2D(Vec2f(x0, y0), Vec2f(u0, v0)),
                    Vertex2D(Vec2f(x1, y0), Vec2f(u1, v0)),
                    Vertex2D(Vec2f(x1, y1), Vec2f(u1, v1)),

                    Vertex2D(Vec2f(x1, y1), Vec2f(u1, v1)),
                    Vertex2D(Vec2f(x0, y1), Vec2f(u0, v1)),
                    Vertex2D(Vec2f(x0, y0), Vec2f(u0, v0))
            };

            for (auto &point: points) {
                allPoints.push_back(point);
            }

            // Move the cursor for the next character, scaling the width by the font size
            x += scaledW;
        }
    }

    mVa = VertexArray(allPoints);
}


}