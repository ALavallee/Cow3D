#ifndef COW3D_TEXTURE_H
#define COW3D_TEXTURE_H

#include <vector>
#include <string>
#include "GlLoader.h"
#include "Color.h"

namespace cow {

class Texture {

public:

    static Texture &Default();

    Texture();

    void load(char *data, size_t size);

    void load(std::string path);

    void load(std::vector<Color> pixels, int w, int h);

    void use() const;

    int getWidth();

    int getHeight();

    void setFilter(GLenum min, GLenum mag);

    void setWrap(GLenum s, GLenum t);

    bool isLoaded();

private:
    GLuint mId;
    int mWidth, mHeight;

    static Texture *defaultInstance;

};

}

#endif //COW3D_TEXTURE_H
