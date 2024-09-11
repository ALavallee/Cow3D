#ifndef EVOCLIENT_SHADER_H
#define EVOCLIENT_SHADER_H

#include <string>
#include <vector>
#include "math/Vec2.h"
#include "math/Vec3.h"
#include "math/Mat4.h"
#include "math/Vec4.h"
#include "render/GlLoader.h"

namespace cow {

class Shader {

public:
    Shader();

    ~Shader();

    void loadFromSource(std::string vertex, std::string fragment);

    void loadFromPath(std::string vertex, std::string fragment);

    void use();


    void setUniformVec2(const std::string &name, Vec2f value);

    void setUniformVec3(const std::string &name, Vec3f value);

    void setUniformVec4(const std::string &name, Vec4f value);

    void setUniformMat4(const std::string &name, Mat4 value);

    void setUniformMat4(const std::string &name, std::vector<Mat4> &value);

private:

    GLuint compile(GLenum type, std::string &source);

    GLuint mProgram;
};

}

#endif //EVOCLIENT_SHADER_H
