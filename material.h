#pragma once


#include <GL/glew.h>
#include <GL/gl.h>

//class Shader;

class Material {
public:
    //Material(Shader vertex_shader, Shader fragment_shader);
    Material(GLuint vertex_shader, GLuint fragment_shader);

    //Material(const Material&) = delete;
    //Material& operator=(const Material&) = delete;

    GLuint handle();

private:
    GLuint program_id;
};