
#include "mesh_triangle.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

MeshTriangle::MeshTriangle():
    Mesh() {

    static const GLfloat tri_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.5f, 1.0f, 0.0f,

        // 1.0f, 0.0f, 0.0f,
        // 1.0f, 0.0f, 1.0f,
        // 0.0f, 1.0f, 0.0f
    };

    index_count = sizeof(tri_data);

	glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

	glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tri_data), tri_data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
	);

    // glEnableVertexAttribArray(1);
    // glVertexAttribPointer(
    //     1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
    //     3,                  // size
    //     GL_FLOAT,           // type
    //     GL_FALSE,           // normalized?
    //     0,                  // stride
    //     (void*)0            // array buffer offset
    // );


    //glBindVertexArray(0);
}