#include "Shader.h"
#include "other/File.h"

namespace cow {

Shader::Shader() : mProgram(0) {

}

Shader::~Shader() {
    //glDeleteProgram (mProgram);
}

void Shader::loadFromSource(std::string vertex, std::string fragment) {
    GLuint vertexProgram = compile(GL_VERTEX_SHADER, vertex);
    GLuint fragmentProgram = compile(GL_FRAGMENT_SHADER, fragment);
    mProgram = glCreateProgram();
    glAttachShader(mProgram, vertexProgram);
    glAttachShader(mProgram, fragmentProgram);
    glLinkProgram(mProgram);

    // Check for linking errors
    GLint status;
    glGetProgramiv(mProgram, GL_LINK_STATUS, &status);
    if (!status) {
        char buffer[512];
        glGetProgramInfoLog(mProgram, 512, NULL, buffer);
        fprintf(stderr, "Shader link error: %s\n", buffer);
    }

    glDeleteShader(vertexProgram);
    glDeleteShader(fragmentProgram);
}

void Shader::loadFromPath(std::string vertex, std::string fragment) {
    loadFromSource(File::LoadEntireStringFromPath(vertex), File::LoadEntireStringFromPath(fragment));
}

void Shader::use() {
    glUseProgram(mProgram);
}

void Shader::setUniformVec2(const std::string &name, Vec2f value) {
    GLint location = glGetUniformLocation(mProgram, const_cast<char *>(name.c_str()));
    if (location == -1) {
        std::cout << "Uniform '" << name << "' not found.\n";
    } else {
        glUniform2fv(location, 1, reinterpret_cast<float *>(&value));
    }
}

void Shader::setUniformVec3(const std::string &name, Vec3f value) {
    GLint location = glGetUniformLocation(mProgram, const_cast<char *>(name.c_str()));
    if (location == -1) {
        std::cout << "Uniform '" << name << "' not found.\n";
    } else {
        glUniform3fv(location, 1, reinterpret_cast<float *>(&value));
    }
}

void Shader::setUniformVec4(const std::string &name, Vec4f value) {
    GLint location = glGetUniformLocation(mProgram, const_cast<char *>(name.c_str()));
    if (location == -1) {
        std::cout << "Uniform '" << name << "' not found.\n";
    } else {
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }
}

void Shader::setUniformMat4(const std::string &name, Mat4 value) {
    GLint location = glGetUniformLocation(mProgram, const_cast<char *>(name.c_str()));
    if (location == -1) {
        std::cout << "Uniform '" << name << "' not found.\n";
    } else {
        glUniformMatrix4fv(location, 1, GL_FALSE, reinterpret_cast<float *>(&value));
    }
}

void Shader::setUniformMat4(const std::string &name, std::vector<Mat4> &value) {
    GLint location = glGetUniformLocation(mProgram, const_cast<char *>(name.c_str()));
    if (location == -1) {
        std::cout << "Uniform '" << name << "' not found.\n";
    } else {
        glUniformMatrix4fv(location, value.size(), GL_FALSE, reinterpret_cast<float *>(value.data()));
    }
}

GLuint Shader::compile(GLenum type, std::string &source) {
    GLuint shader = glCreateShader(type);
    char *rawSource = const_cast<char *>(source.c_str());
    glShaderSource(shader, 1, &rawSource, NULL);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        char buffer[512];
        glGetShaderInfoLog(shader, 512, NULL, buffer);
        fprintf(stderr, "Shader compile error: %s\n", buffer);
        return 0;
    }

    return shader;
}

}