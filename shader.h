#pragma once

#include <string>

#include <GL/glew.h>
#include <GL/gl.h>

#include <glm/glm.hpp>

enum class ShaderType {
    VERTEX,
    GEOMETRY,
    FRAGMENT
};

GLuint load_shaders(const char * vertex_file_path, const char * fragment_file_path);

class Texture;

class Shader {
public:
    Shader() = default;
    Shader(const char* vs_path, const char* fs_path);
    Shader(const char* vs_path, const char* fs_path, const char* gs_path);

    void use_program();
    void set_uniform(std::string id, glm::vec3 v);
    void set_uniform(std::string id, glm::mat4 m4);

    void set_texture(std::string name, Texture texture, GLenum texture_unit);
    GLuint get_program() const;

private:
    std::string load_shader(const std::string path);
    void compile_shader(const std::string& shader_code, ShaderType type);
    void post_compile_check(GLuint shader_type);
    void link_shader();
    void cleanup_shader();

private:
    std::string shader_from_path;

    GLuint vertex_id;
    GLuint fragment_id;
    GLuint geometry_id;
    GLuint program_id;
};
