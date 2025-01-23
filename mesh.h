#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

//enum class GeometryType { Triangle, Quad, Cube, Plane};//??


class Mesh {
public:
    GLuint get_index_count() const;
    void bind() const;
    void unbind() const;
    void cleanup() const;

protected:
    GLuint index_count;

    GLuint vao;
    GLuint vbo;
};



