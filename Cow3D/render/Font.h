#ifndef COW3D_FONT_H
#define COW3D_FONT_H

#include <vector>
#include "ext/stb/stb_truetype.h"
#include "math/Rect.h"
#include "render/Texture.h"

namespace cow {

struct Glyph {

    Glyph() {}

    Glyph(Recti box) : box(box) {}

    Recti box;
};

class Font {

public:

    static constexpr int DefaultFontSize = 64;

    static Font *Default();

    Font();

    bool loadFromFile(std::string path);

    bool loadFromData(std::vector<char> &data);

    Texture &getTexture();

    Glyph getGlyph(char index);

private:

    static Font *defaultFont;
    stbtt_fontinfo mInfo{};
    std::vector<Glyph> mGlyphs;
    Texture mTexture;

};

}

#endif //COW3D_FONT_H
