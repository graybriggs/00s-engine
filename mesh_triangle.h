#pragma once

#include "renderable_mesh.h"

class RMeshTriangle : public RMesh {
public:
    RMeshTriangle();
    
    GLuint get_index_count() const override;
    void bind() const override;
    void unbind() const override;
    void cleanup() const override;

private:
    GLuint index_count;

    GLuint vao;
    GLuint vbo_tri;
    GLuint texture;
    GLuint tex_uv;
};
