#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION

#include "ext/stb/stb_image.h"
#include "other/Logger.h"

namespace cow {

Texture *Texture::defaultInstance = nullptr;

Texture &Texture::Default() {
    if (defaultInstance == nullptr) {
        defaultInstance = new Texture();
        defaultInstance->load({Color::white()}, 1, 1);
    }

    return *defaultInstance;
}

Texture::Texture() : mId(0), mWidth(0), mHeight(0) {

}

void Texture::load(char *data, size_t size) {
    // Load image data
    int width, height, channels;
    unsigned char *imageData = stbi_load_from_memory(reinterpret_cast<const stbi_uc *>(data),
                                                     static_cast<int>(size), &width, &height, &channels, 0);
    if (!imageData) {
        Logger::Log("Failed to load texture data");
        return;
    }

    GLint format;
    if (channels == 1) {
        format = GL_RED;
    } else if (channels == 3) {
        format = GL_RGB;
    } else if (channels == 4) {
        format = GL_RGBA;
    } else {
        format = GL_RGBA;
    }

    glGenTextures(1, &mId);
    glBindTexture(GL_TEXTURE_2D, mId);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    float anisotropy = gl_get_anisotropy();
    if (anisotropy > 0.f) {
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, gl_get_anisotropy());
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);


    stbi_image_free(imageData);
    glBindTexture(GL_TEXTURE_2D, 0);

    mWidth = width;
    mHeight = height;

}

void Texture::load(std::string path) {
    int width, height, channels;
    unsigned char *imageData = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if (!imageData) {
        Logger::Log("Failed to load texture file:" + path);
        return;
    }

    GLint format;
    if (channels == 1) {
        format = GL_RED;
    } else if (channels == 3) {
        format = GL_RGB;
    } else if (channels == 4) {
        format = GL_RGBA;
    }

    glGenTextures(1, &mId);
    glBindTexture(GL_TEXTURE_2D, mId);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    float anisotropy = gl_get_anisotropy();
    if (anisotropy > 0.f) {
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, gl_get_anisotropy());
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);


    stbi_image_free(imageData);
    glBindTexture(GL_TEXTURE_2D, 0);

    mWidth = width;
    mHeight = height;
}

void Texture::load(std::vector<Color> pixels, int w, int h) {
    glGenTextures(1, &mId);
    glBindTexture(GL_TEXTURE_2D, mId);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload the texture data to the GPU
    mWidth = w;
    mHeight = h;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());


    float anisotropy = gl_get_anisotropy();
    if (anisotropy > 0.f) {
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, gl_get_anisotropy());
    }

    // Generate mipmaps after the texture data is uploaded
    glGenerateMipmap(GL_TEXTURE_2D);

    // Unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::use() const {
    glBindTexture(GL_TEXTURE_2D, mId);
}

int Texture::getWidth() {
    return mWidth;
}

int Texture::getHeight() {
    return mHeight;
}

void Texture::setFilter(GLenum min, GLenum mag) {
    glBindTexture(GL_TEXTURE_2D, mId); // Bind the texture to set its parameters


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);

    glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture
}

void Texture::setWrap(GLenum s, GLenum t) {
    glBindTexture(GL_TEXTURE_2D, mId); // Bind the texture to set its parameters

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t);

    glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture
}

bool Texture::isLoaded() {
    return mId != 0;
}

}