

#include "mesh_line.h"

RMeshLine::RMeshLine() {

    static const float line_geometry[] = {
        -1.0f, 0.0f, 0.0f,
         1.0f, 0.0f, 0.0f
    };

    static const float line_colors[] = {
        1.0f, 1.0f, 1.0f,  // white
        1.0f, 1.0f, 1.0f // white
    };

    std::vector<GLuint> idx = {
        0, 1
    };
    indices = std::move(idx);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // geometry

    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(line_geometry), line_geometry, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void*)0  
    );

    // color info

    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(line_colors), line_colors, GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void*)0  
    );

    // indices

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
}

GLuint RMeshLine::get_index_count() const {
    return static_cast<GLuint>(indices.size());
}

void RMeshLine::bind() const {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);

}

void RMeshLine::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RMeshLine::cleanup() const {

}