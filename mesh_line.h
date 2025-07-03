#pragma once

#include "renderable_mesh.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include <vector>

class RMeshLine : public RMesh {
public:

    RMeshLine();

    virtual GLuint get_index_count() const;
    virtual void bind() const;
    virtual void unbind() const;
    virtual void cleanup() const;

private:
    std::vector<GLuint> indices;

    GLuint vao;
    GLuint vbo;
    GLuint vbo_col;
    GLuint ebo;
};
