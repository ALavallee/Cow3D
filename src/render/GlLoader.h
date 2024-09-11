#ifndef COW3D_GL_LOADER_H
#define COW3D_GL_LOADER_H

#include <GL/gl.h>
#include <stdbool.h>

#define GL_TEXTURE0 0x84C0

#define GL_NUM_EXTENSIONS 0x821D
#define GL_COMPILE_STATUS 0x8B81
#define GL_VERTEX_SHADER  0x8B31
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_LINK_STATUS 0x8B82
#define GL_ARRAY_BUFFER 0x8892
#define GL_STATIC_DRAW 0x88E4
#define GL_ELEMENT_ARRAY_BUFFER 0x8893
#define GL_SHADER_STORAGE_BUFFER 0x90D2
#define GL_MULTISAMPLE 0x809D
#define GL_CLAMP_TO_EDGE 0x812F
#define GL_MIRROR_CLAMP_TO_EDGE 0x8743
#define GL_MIRRORED_REPEAT 0x8370
#define GL_LINEAR_MIPMAP_LINEAR 0x2703
#define GL_TEXTURE_3D 0x806F
#define GL_TEXTURE_WRAP_R 0x8072
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
#define GL_STREAM_DRAW 0x88E0
#define GL_WRITE_ONLY 0x88B9
#define GL_FUNC_ADD 0x8006

#define WGL_DRAW_TO_WINDOW_ARB 0x2001
#define WGL_SUPPORT_OPENGL_ARB 0x2010
#define WGL_DOUBLE_BUFFER_ARB 0x2011
#define WGL_PIXEL_TYPE_ARB 0x2013
#define WGL_TYPE_RGBA_ARB 0x202B
#define WGL_COLOR_BITS_ARB 0x2014
#define WGL_DEPTH_BITS_ARB 0x2022
#define WGL_STENCIL_BITS_ARB 0x2023
#define WGL_SAMPLE_BUFFERS_ARB 0x2041
#define WGL_SAMPLES_ARB 0x2042

typedef size_t GLsizeiptr;
typedef char GLchar;

#define APIENTRYP APIENTRY *

typedef GLuint (APIENTRYP PFNGLCREATESHADERTYPE)(GLenum shaderType);

typedef void (APIENTRYP PFNGLSHADERSOURCEPROC)(GLuint shader, GLsizei count, char **string, const GLint *length);

typedef void (APIENTRYP PFNGLCOMPILESHADERPROC)(GLuint shader);

typedef void (APIENTRYP PFNGLGETSHADERIVPROC)(GLuint shader, GLenum pname, GLint *params);

typedef void (APIENTRYP PFNGLGETSHADERINFOLOGPROC)(GLuint shader, GLsizei bufSize, GLsizei *length, char *infoLog);

typedef GLuint (APIENTRYP PFNGLCREATEPROGRAMPROC)(void);

typedef void (APIENTRYP PFNGLATTACHSHADERPROC)(GLuint program, GLuint shader);

typedef void (APIENTRYP PFNGLLINKPROGRAMPROC)(GLuint program);

typedef void (APIENTRYP PFNGLUSEPROGRAMPROC)(GLuint program);

typedef GLint (APIENTRYP PFNGLGETUNIFORMLOCATIONPROC)(GLuint program, char *name);

typedef void (APIENTRYP PFNGLACTIVETEXTUREPROC)(GLenum texture);

typedef void (APIENTRYP PFNGLGENTEXTURESPROC)(GLsizei n, GLuint *textures);

typedef void (APIENTRYP PFNGLBINDTEXTUREPROC)(GLenum target, GLuint texture);

typedef void (APIENTRYP PFNGLTEXIMAGE2DPROC)(GLenum target, GLint level, GLint internalformat, GLsizei width,
                                             GLsizei height, GLint border, GLenum format, GLenum type,
                                             const void *pixels);

typedef void (APIENTRYP PFNGLTEXPARAMETERIPROC)(GLenum target, GLenum pname, GLint param);

typedef void (APIENTRYP PFNGLGENBUFFERSPROC)(GLsizei n, GLuint *buffers);

typedef void (APIENTRYP PFNGLBINDBUFFERPROC)(GLenum target, GLuint buffer);

typedef void (APIENTRYP PFNGLBUFFERDATAPROC)(GLenum target, GLsizeiptr size, const void *data, GLenum usage);

typedef void (APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized,
                                                      GLsizei stride, const void *pointer);

typedef void (APIENTRYP PFNGLVERTEXATTRIBIPOINTERPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized,
                                                       GLsizei stride, const void *pointer);

typedef void (APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint index);

typedef void (APIENTRYP PFNGLDRAWARRAYSPROC)(GLenum mode, GLint first, GLsizei count);

typedef void (APIENTRYP PFNGLDRAWELEMENTSPROC)(GLenum mode, GLsizei count, GLenum type, const void *indices);

typedef void (APIENTRYP PFNGLGENVERTEXARRAYSPROC)(GLsizei n, GLuint *arrays);

typedef void (APIENTRYP PFNGLBINDVERTEXARRAYPROC)(GLuint array);

typedef void (APIENTRYP PFNGLGETPROGRAMIVPROC)(GLuint program, GLenum pname, GLint *params);

typedef void (APIENTRYP PFNGLGETPROGRAMINFOLOGPROC)(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);

typedef void (APIENTRYP PFNGLDELETESHADERPROC)(GLuint shader);

typedef void (APIENTRYP PFNGLUNIFORM1FVPROC)(GLint location, GLsizei count, const GLfloat *value);

typedef void (APIENTRYP PFNGLUNIFORM2FVPROC)(GLint location, GLsizei count, const GLfloat *value);

typedef void (APIENTRYP PFNGLUNIFORM3FVPROC)(GLint location, GLsizei count, const GLfloat *value);

typedef void (APIENTRYP PFNGLDELETEBUFFERSPROC)(GLsizei n, const GLuint *buffers);

typedef void (APIENTRYP PFNGLDELETEVERTEXARRAYSPROC)(GLsizei n, const GLuint *arrays);

typedef void (APIENTRYP PFNGLUNIFORMMATRIX4FVPROC)(GLint location, GLsizei count, GLboolean transpose,
                                                   const GLfloat *value);

typedef void (APIENTRYP PFNGLUNIFORM1IPROC)(GLint location, GLint value);

typedef void (APIENTRYP PFNGLUNIFORM4FPROC)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

typedef void (APIENTRYP PFNGLUNIFORM4IPROC)(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);

typedef void (APIENTRYP PFNGLGENERATEMIPMAPPROC)(GLenum target);

typedef void (APIENTRYP PFNGLBINDBUFFERBASEPROC)(GLenum target, GLuint index, GLuint buffer);

typedef void (APIENTRYP PFNGLTEXIMAGE3DPROC)(GLenum target, GLint level, GLint internalFormat, GLsizei width,
                                             GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type,
                                             const void *pixels);

typedef void (APIENTRYP PFNGLTEXSUBIMAGE3DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset,
                                                GLsizei width, GLsizei height, GLsizei depth, GLenum format,
                                                GLenum type,
                                                const void *pixels);

typedef void (APIENTRYP PFNGLVERTEXATTRIBDIVISORPROC)(GLuint index, GLuint divisor);

typedef void (APIENTRYP PFNGLDRAWARRAYSINSTANCEDPROC)(GLenum mode, GLint first, GLsizei count, GLsizei instancecount);

typedef void *(APIENTRYP PFNGLMAPBUFFERPROC)(GLenum target, GLenum access);

typedef GLboolean (APIENTRYP PFNGLUNMAPBUFFERPROC)(GLenum target);

typedef void (APIENTRYP PFNGLBLENDEQUATIONPROC)(GLenum mode);

typedef int (APIENTRYP PFNGLGETATTRIBLOCATION)(GLuint program, const GLchar *name);

typedef const GLubyte *(APIENTRYP PFNGLGETSTRINGIPROC)(GLenum name, GLuint index);


extern PFNGLCREATESHADERTYPE glCreateShader;
extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
extern PFNGLACTIVETEXTUREPROC glActiveTexture;
extern PFNGLGENBUFFERSPROC glGenBuffers;
extern PFNGLBINDBUFFERPROC glBindBuffer;
extern PFNGLBUFFERDATAPROC glBufferData;
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
extern PFNGLVERTEXATTRIBIPOINTERPROC glVertexAttribIPointer;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
extern PFNGLDELETESHADERPROC glDeleteShader;
extern PFNGLUNIFORM1FVPROC glUniform1fv;
extern PFNGLUNIFORM2FVPROC glUniform2fv;
extern PFNGLUNIFORM3FVPROC glUniform3fv;
extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;
extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
extern PFNGLUNIFORM1IPROC glUniform1i;
extern PFNGLUNIFORM4FPROC glUniform4f;
extern PFNGLUNIFORM4IPROC glUniform4i;
extern PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
extern PFNGLBINDBUFFERBASEPROC glBindBufferBase;
extern PFNGLTEXIMAGE3DPROC glTexImage3D;
extern PFNGLTEXSUBIMAGE3DPROC glTexSubImage3D;
extern PFNGLVERTEXATTRIBDIVISORPROC glVertexAttribDivisor;
extern PFNGLDRAWARRAYSINSTANCEDPROC glDrawArraysInstanced;
extern PFNGLMAPBUFFERPROC glMapBuffer;
extern PFNGLUNMAPBUFFERPROC glUnmapBuffer;
extern PFNGLBLENDEQUATIONPROC glBlendEquation;
extern PFNGLGETATTRIBLOCATION glGetAttribLocation;
extern PFNGLGETSTRINGIPROC glGetStringi;

namespace cow {

void gl_load();

int gl_check_error();

bool gl_is_extension_supported(const char *ext_name);

float gl_get_anisotropy();

}

#endif //COW3D_GL_LOADER_H
