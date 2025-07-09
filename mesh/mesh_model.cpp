
#include "../mesh_data.h"
#include "mesh_model.h"
#include "renderable_mesh.h"


#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include <algorithm>
#include <ranges>

RMeshModel::RMeshModel(const MeshData& md) {

    indices = md.model_vertex_indices_data;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * md.model_vertex_data.size(), &md.model_vertex_data[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &vbo_col);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_col);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * md.model_vertex_data.size(), &md.model_vertex_data[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &vbo_normal);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_normal);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * md.model_vertex_normal_data.size(), &md.model_vertex_normal_data[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * md.model_vertex_indices_data.size(), &md.model_vertex_indices_data[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
}

GLuint RMeshModel::get_index_count() const {
    return static_cast<GLuint>(indices.size());
}

void RMeshModel::bind() const {
    glBindVertexArray(vao);
}

void RMeshModel::unbind() const {
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RMeshModel::cleanup() const {

}