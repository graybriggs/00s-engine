
#include "mesh_quad.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>


RMeshQuad::RMeshQuad() {
    
    const float quad_geometry[] = {
        -1.0f, -1.0f, 0.0f,  // 0.0f, 1.0f, 1.0f,
		 1.0f, -1.0f, 0.0f,  // 1.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,  // 0.0f, 0.0f, 1.0f,
		-1.0f,  1.0f, 0.0f,  // 0.0f, 1.0f, 0.0f,
    };

    const float quad_uv[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };

    std::vector<GLuint> idx = {
        0, 1, 2,   // first triangle
        2, 3, 0    // second triangle
    };

    indices = std::move(idx);


    glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
    
    //
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_geometry), quad_geometry, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    //
    glGenBuffers(1, &tex_uv);
    glBindBuffer(GL_ARRAY_BUFFER, tex_uv);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_uv), quad_uv, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(0));
    glEnableVertexAttribArray(1);

    //
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
}

GLuint RMeshQuad::get_index_count() const {
    return static_cast<GLuint>(indices.size());
}

void RMeshQuad::bind() const {
    glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

void RMeshQuad::unbind() const {
    glBindVertexArray(0);
}

void RMeshQuad::cleanup() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}