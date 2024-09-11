#include "GlLoader.h"
#include <string.h>
#include <SDL3/SDL.h>
#include <iostream>

typedef PROC (*wglGetProcAddressFP)(LPCSTR Arg1);

static HMODULE openGLLibHandle = NULL;

PFNGLCREATESHADERTYPE glCreateShader;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
PFNGLACTIVETEXTUREPROC glActiveTexture;
PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLBUFFERDATAPROC glBufferData;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
PFNGLVERTEXATTRIBIPOINTERPROC glVertexAttribIPointer;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
PFNGLGETPROGRAMIVPROC glGetProgramiv;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
PFNGLDELETESHADERPROC glDeleteShader;
PFNGLUNIFORM1FVPROC glUniform1fv;
PFNGLUNIFORM2FVPROC glUniform2fv;
PFNGLUNIFORM3FVPROC glUniform3fv;
PFNGLDELETEBUFFERSPROC glDeleteBuffers;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
PFNGLUNIFORM1IPROC glUniform1i;
PFNGLUNIFORM4FPROC glUniform4f;
PFNGLUNIFORM4IPROC glUniform4i;
PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
PFNGLBINDBUFFERBASEPROC glBindBufferBase;
PFNGLTEXIMAGE3DPROC glTexImage3D;
PFNGLTEXSUBIMAGE3DPROC glTexSubImage3D;
PFNGLVERTEXATTRIBDIVISORPROC glVertexAttribDivisor;
PFNGLDRAWARRAYSINSTANCEDPROC glDrawArraysInstanced;
PFNGLMAPBUFFERPROC glMapBuffer;
PFNGLUNMAPBUFFERPROC glUnmapBuffer;
PFNGLBLENDEQUATIONPROC glBlendEquation;
PFNGLGETATTRIBLOCATION glGetAttribLocation;
PFNGLGETSTRINGIPROC glGetStringi;


static void *load_opengl_function(const char *name) {
    void *fn = reinterpret_cast<void *>(SDL_GL_GetProcAddress(name));

    if (fn == NULL) {
        printf("Can't load OpenGL function %s\n", name);
    }

    return fn;
}

namespace cow {

void gl_load() {
    glCreateShader = (PFNGLCREATESHADERTYPE) (load_opengl_function("glCreateShader"));
    glShaderSource = (PFNGLSHADERSOURCEPROC) (load_opengl_function("glShaderSource"));
    glCompileShader = (PFNGLCOMPILESHADERPROC) (load_opengl_function("glCompileShader"));
    glGetShaderiv = (PFNGLGETSHADERIVPROC) (load_opengl_function("glGetShaderiv"));
    glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) (load_opengl_function("glGetShaderInfoLog"));
    glCreateProgram = (PFNGLCREATEPROGRAMPROC) (load_opengl_function("glCreateProgram"));
    glAttachShader = (PFNGLATTACHSHADERPROC) (load_opengl_function("glAttachShader"));
    glLinkProgram = (PFNGLLINKPROGRAMPROC) (load_opengl_function("glLinkProgram"));
    glUseProgram = (PFNGLUSEPROGRAMPROC) (load_opengl_function("glUseProgram"));
    glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) (load_opengl_function("glGetUniformLocation"));
    glActiveTexture = (PFNGLACTIVETEXTUREPROC) (load_opengl_function("glActiveTexture"));
    glGenBuffers = (PFNGLGENBUFFERSPROC) (load_opengl_function("glGenBuffers"));
    glBindBuffer = (PFNGLBINDBUFFERPROC) (load_opengl_function("glBindBuffer"));
    glBufferData = (PFNGLBUFFERDATAPROC) (load_opengl_function("glBufferData"));
    glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC) (load_opengl_function("glVertexAttribPointer"));
    glVertexAttribIPointer = (PFNGLVERTEXATTRIBIPOINTERPROC) (load_opengl_function("glVertexAttribIPointer"));
    glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC) (load_opengl_function("glEnableVertexAttribArray"));
    glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC) (load_opengl_function("glGenVertexArrays"));
    glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC) (load_opengl_function("glBindVertexArray"));
    glGetProgramiv = (PFNGLGETPROGRAMIVPROC) (load_opengl_function("glGetProgramiv"));
    glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC) (load_opengl_function("glGetProgramInfoLog"));
    glDeleteShader = (PFNGLDELETESHADERPROC) (load_opengl_function("glDeleteShader"));
    glUniform1fv = (PFNGLUNIFORM1FVPROC) (load_opengl_function("glUniform1fv"));
    glUniform2fv = (PFNGLUNIFORM2FVPROC) (load_opengl_function("glUniform2fv"));
    glUniform3fv = (PFNGLUNIFORM2FVPROC) (load_opengl_function("glUniform3fv"));
    glDeleteBuffers = (PFNGLDELETEBUFFERSPROC) (load_opengl_function("glDeleteBuffers"));
    glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC) (load_opengl_function("glDeleteVertexArrays"));
    glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC) (load_opengl_function("glUniformMatrix4fv"));
    glUniform1i = (PFNGLUNIFORM1IPROC) (load_opengl_function("glUniform1i"));
    glUniform4f = (PFNGLUNIFORM4FPROC) (load_opengl_function("glUniform4f"));
    glUniform4i = (PFNGLUNIFORM4IPROC) (load_opengl_function("glUniform4i"));
    glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC) (load_opengl_function("glGenerateMipmap"));
    glTexImage3D = (PFNGLTEXIMAGE3DPROC) (load_opengl_function("glTexImage3D"));
    glTexSubImage3D = (PFNGLTEXSUBIMAGE3DPROC) (load_opengl_function("glTexSubImage3D"));
    glBindBufferBase = (PFNGLBINDBUFFERBASEPROC) (load_opengl_function("glBindBufferBase"));
    glVertexAttribDivisor = (PFNGLVERTEXATTRIBDIVISORPROC) (load_opengl_function("glVertexAttribDivisor"));
    glDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC) (load_opengl_function("glDrawArraysInstanced"));
    glMapBuffer = (PFNGLMAPBUFFERPROC) (load_opengl_function("glMapBuffer"));
    glUnmapBuffer = (PFNGLUNMAPBUFFERPROC) (load_opengl_function("glUnmapBuffer"));
    glBlendEquation = (PFNGLBLENDEQUATIONPROC) (load_opengl_function("glBlendEquation"));
    glGetAttribLocation = (PFNGLGETATTRIBLOCATION) (load_opengl_function("glGetAttribLocation"));
    glGetStringi = (PFNGLGETSTRINGIPROC) (load_opengl_function("glGetStringi"));
}

const char *getErrorString(GLenum error) {
    switch (error) {
        case GL_NO_ERROR:
            return "No error";
        case GL_INVALID_ENUM:
            return "Invalid enum";
        case GL_INVALID_VALUE:
            return "Invalid value";
        case GL_INVALID_OPERATION:
            return "Invalid operation";
        case GL_STACK_OVERFLOW:
            return "Stack overflow";
        case GL_STACK_UNDERFLOW:
            return "Stack underflow";
        case GL_OUT_OF_MEMORY:
            return "Out of memory";
        default:
            return "Unknown error";
    }
}

int gl_check_error() {
    int err_count = 0;
    GLenum errCode;
    while ((errCode = glGetError()) != GL_NO_ERROR) {
        ++err_count;
        std::cerr << "OpenGL Error: " << std::string(getErrorString(errCode));
    }

    return err_count;
}

bool gl_is_extension_supported(const char *ext_name) {
    GLint numExtensions;
    glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);

    for (GLint i = 0; i < numExtensions; ++i) {
        const GLubyte *extension = glGetStringi(GL_EXTENSIONS, i);
        if (strcmp(reinterpret_cast<const char *>(extension), ext_name) == 0) {
            return true;
        }
    }

    return false;
}

float gl_get_anisotropy() {
    if (gl_is_extension_supported("GL_EXT_texture_filter_anisotropic")) {
        GLfloat largest;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest);
        return (float) largest;
    }
    return 0;
}

}
