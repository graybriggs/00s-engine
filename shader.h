#pragma once

#include <GL/glew.h>
#include <GL/gl.h>

enum class ShaderType { VERTEX, GEOMETRY, FRAGMENT };

GLuint load_shaders(const char * vertex_file_path, const char * fragment_file_path);


class Shader {
public:
    Shader() = default;
    Shader(const char* path, const ShaderType type);
    GLuint handle() const;

private:
    // could be various compiled shader types stored in a vector? that can be selected
    ShaderType shader_type;
    GLuint shader_id;
};


#include <string>

class Shader_ {
public:
    Shader_() = default;
    Shader_(const char* vs_path, const char* fs_path);
    Shader_(const char* vs_path, const char* fs_path, const char* gs_path);

private:

    std::string load_shader(std::string path);
    void compile_shader(ShaderType type);
    void post_compile_check();
    void link_shader();
    void cleanup_shader();

private:

    std::string shader_code;
    std::string shader_from_path;

    GLuint vertex_id;
    GLuint fragment_id;
    GLuint geometry_id;
    GLuint program_id;
};
