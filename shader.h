#pragma once

#include <GL/glew.h>
#include <GL/gl.h>

enum class ShaderType { VERTEX, GEOMETRY, FRAGMENT };

GLuint load_shaders(const char * vertex_file_path, const char * fragment_file_path);


class Shader {
public:
    Shader(const char* path, const ShaderType type);
    GLuint handle() const;

private:
    // could be various compiled shader types stored in a vector? that can be selected
    ShaderType shader_type;
    GLuint shader_id;
};

