#pragma once

#include "renderable_mesh.h"

#include <vector>

class RMeshCube : public RMesh {
public:
    RMeshCube();

    GLuint get_index_count() const override;
    void bind() const override;
    void unbind() const override;
    void cleanup() const override;

private:
    std::vector<GLuint> indices;
    GLuint index_count;

    GLuint vao;
    GLuint vbo;
    GLuint vbo_col;
    GLuint texture;
    GLuint tex_uv;
};