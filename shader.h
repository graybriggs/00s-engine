#pragma once
#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GL/gl.h>

enum class ShaderType { VERTEX, FRAGMENT };

GLuint load_shaders(const char * vertex_file_path, const char * fragment_file_path);

// GLuint vertex_shader(const char* vs_path);
// GLuint fragment_shader(const char* fs_path);

// GLuint load_compile_shader(const char* path);


class Shader {
public:
    Shader(const char* path, const ShaderType type);
    GLuint handle() const;

private:
    // could be various compiled shader types stored in a vector? that can be selected
    ShaderType shader_type;
    GLuint shader_id;
};

#endif
