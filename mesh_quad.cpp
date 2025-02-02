
#include "mesh_quad.h"

RMeshQuad::RMeshQuad() {
    
    const float vertex_data_quad[] = {
        -1.0f, 1.0f, 0.0f,   0.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 0.0f,   1.0f, 0.0f, 0.0f,
		 1.0f,-1.0f, 0.0f,   0.0f, 0.0f, 1.0f,
		-1.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
		 1.0f, 1.0f, 0.0f,   1.0f, 0.0f, 1.0f,
		 1.0f,-1.0f, 0.0f,   1.0f, 1.0f, 0.0f,
    };

    glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data_quad), vertex_data_quad, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
}

GLuint RMeshQuad::get_index_count() const {
    return 6;
}

void RMeshQuad::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_col);
}

void RMeshQuad::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RMeshQuad::cleanup() const {

}