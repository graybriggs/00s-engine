

#include "mesh_terrain.h"

#include "terrain_data.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

RMeshTerrain::RMeshTerrain(const TerrainData& td) {

    indices = td.indices;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * td.vertices.size(), &td.vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * td.indices.size(), &td.indices[0], GL_STATIC_DRAW);


    glBindVertexArray(0);
}

GLuint RMeshTerrain::get_index_count() const {
    return static_cast<GLuint>(indices.size());
}

void RMeshTerrain::bind() const {
    glBindVertexArray(vao);
}

void RMeshTerrain::unbind() const {
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RMeshTerrain::cleanup() const {
    
}