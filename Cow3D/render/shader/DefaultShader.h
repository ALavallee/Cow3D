#ifndef COW3D_DEFAULTSHADER_H
#define COW3D_DEFAULTSHADER_H

#include <string>

namespace cow {

class DefaultShader {

public:

    constexpr static const std::string_view ScreenFragment = R"(
        #version 430 core

        in vec2 texCoords;
        uniform sampler2D textureSample;
        uniform vec4 color;
        out vec4 FragColor;

        void main()
        {
            FragColor = texture(textureSample, texCoords) * color;
        }
    )";

    constexpr static const std::string_view ScreenVertex = R"(
        #version 430 core
        layout(location = 0) in vec2 aPos;
        layout(location = 1) in vec2 aTex;

        uniform mat4 camera;
        uniform vec4 color;
        uniform vec2 pos;

        out vec2 texCoords;

        void main()
        {
            // Translate the position by 'pos' and apply the camera transformation
            gl_Position = camera * vec4(aPos + pos, 0.0, 1.0);
            texCoords = aTex;
        }
    )";

    constexpr static const std::string_view ModelVertex = R"(
    #version 430 core

    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec2 aTex;
    layout(location = 2) in vec4 aColor;
    layout(location = 3) in vec4 aJoints;
    layout(location = 4) in vec4 aWeights;

    uniform mat4 model;
    uniform mat4 camera;
    uniform mat4 joint_matrices[150];

    out vec2 texCoords;
    out vec4 vColor;

    void main()
    {
        mat4 skinMatrix;
        if (aJoints.x == -1){
            skinMatrix = mat4(1.0);
        } else {
            skinMatrix = aWeights.x * joint_matrices[int(aJoints.x)] +
            aWeights.y * joint_matrices[int(aJoints.y)] +
            aWeights.z * joint_matrices[int(aJoints.z)] +
            aWeights.w * joint_matrices[int(aJoints.w)];
        }

        gl_Position = camera * (model * (skinMatrix * vec4(aPos, 1.0)));

        texCoords = aTex;
        vColor = aColor;
    }
    )";

    constexpr static const std::string_view ModelFragment = R"(
    #version 430 core

    uniform sampler2D textureSample;

    uniform vec4 color;

    in vec2 texCoords;
    in vec4 vColor;

    out vec4 FragColor;

    void main()
    {
        FragColor = texture(textureSample, texCoords) * vColor * color;
    }
    )";

    constexpr static const std::string_view GeometryVertex = R"(
        #version 430 core
        layout(location = 0) in vec3 aPos;
        layout(location = 1) in vec2 aTex;
        layout(location = 2) in vec4 aColor;

        uniform mat4 camera;
        uniform mat4 model;

        out vec2 texCoords;
        out vec4 vColor;

        void main()
        {
            gl_Position = camera * model * vec4(aPos, 1.0);
            texCoords = aTex;
            vColor = aColor;
        }
    )";


    constexpr static const std::string_view GeometryFragment = R"(
        #version 430 core

        uniform sampler2D textureSample;

        uniform vec4 color;

        in vec2 texCoords;
        in vec4 vColor;

        out vec4 FragColor;

        void main()
        {
            FragColor = texture(textureSample, texCoords) * vColor * color;
        }
    )";


};

}

#endif //COW3D_DEFAULTSHADER_H
