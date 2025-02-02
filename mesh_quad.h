#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>


#include "renderable_mesh.h"



class RMeshQuad : public RMesh {
public:
    RMeshQuad();

    GLuint get_index_count() const override;
    void bind() const override;
    void unbind() const override;
    void cleanup() const override;


private:
    GLuint vao;
    GLuint vbo;
    GLuint vbo_col;

    GLuint texture;

};