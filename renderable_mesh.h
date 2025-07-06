#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include <vector>

//enum class GeometryType { Triangle, Quad, Cube, Plane};//??

class RMesh {
public:
    virtual ~RMesh() = default;
    
    virtual GLuint get_index_count() const = 0;
    virtual void bind() const = 0;
    virtual void unbind() const = 0;
    virtual void cleanup() const = 0;

protected:
    // std::vector<GLuint> indices;

    // GLuint vao;
    // GLuint vbo_tri;
    // GLuint texture;
    // GLuint tex_uv;
    // GLuint ebo;
};



