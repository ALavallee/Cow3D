#include "Font.h"

#include "Cow3D/other/File.h"
#include "ext/Arial.h"

#define STBTT_STATIC
#define STB_TRUETYPE_IMPLEMENTATION

#include "ext/stb/stb_truetype.h"

namespace cow {

Font *Font::defaultFont = nullptr;

Font *Font::Default() {
    if (defaultFont == nullptr) {
        defaultFont = new Font();
        auto data = std::vector<char>(std::begin(ARIAL_TTF), std::end(ARIAL_TTF));
        defaultFont->loadFromData(data);
    }

    return defaultFont;
}

Font::Font() {

}

bool Font::loadFromFile(std::string path) {
    auto data = File::LoadEntireBufferFromPath(path);
    return loadFromData(data);
}

bool Font::loadFromData(std::vector<char> &data) {
    mGlyphs.resize(255);

    stbtt_InitFont(&mInfo, (unsigned char *) data.data(), 0);

    float scale = stbtt_ScaleForPixelHeight(&mInfo, (float) DefaultFontSize);
    int atlas_width = DefaultFontSize * 16; // 16 columns
    int atlas_height = DefaultFontSize * 6; // 6 rows (for ASCII 32-127)
    std::vector<Color> pixels;
    pixels.resize(atlas_width * atlas_height, Color::transparent());

    for (int ch = 32; ch < 128; ++ch) {
        int x0, y0, x1, y1;
        stbtt_GetCodepointBitmapBox(&mInfo, ch, scale, scale, &x0, &y0, &x1, &y1);

        int bw = x1 - x0;
        int bh = y1 - y0;

        int row = (ch - 32) / 16;
        int col = (ch - 32) % 16;

        int x = col * DefaultFontSize;
        int y = row * DefaultFontSize;

        unsigned char *bitmap = stbtt_GetCodepointBitmap(&mInfo, 0, scale, ch, &bw, &bh, 0, 0);

        for (int j = 0; j < bh; ++j) {
            for (int i = 0; i < bw; ++i) {
                int px = x + x0 + i;
                int py = y + y0 + (bh - 1 - j);

                if (px >= 0 && px < atlas_width && py >= 0 && py < atlas_height) {
                    unsigned char pixelValue = bitmap[j * bw + i];
                    if (pixelValue > 0) {
                        pixels[py * atlas_width + px] = (Color) {255, 255, 255, pixelValue};
                    }
                }
            }
        }

        if (bitmap) {
            stbtt_FreeBitmap(bitmap, NULL);
        }

        mGlyphs[(char) ch] = Glyph(Recti(x + x0, y + y0, bw, bh));
    }

    mTexture.load(pixels, atlas_width, atlas_height);
    return true;
}

Texture &Font::getTexture() {
    return mTexture;
}

Glyph Font::getGlyph(char index) {
    return mGlyphs[index];
}
}
