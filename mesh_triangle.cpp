
#include <iostream>

#include "mesh_triangle.h"
#include "texture_loader.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

RMeshTriangle::RMeshTriangle() {

    static const GLfloat tri_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.5f, 1.0f, 0.0f,

        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

     static const GLfloat tri_geometry[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.5f, 1.0f, 0.0f
    };

    static const GLfloat tri_uv[] = {
        0.0f, 0.0f,
        0.5f, 1.0f,
        0.5f, 0.0f,
    };

    //index_count = sizeof(tri_data);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

    glGenBuffers(1, &vbo_tri);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_tri);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tri_geometry), tri_geometry, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,  // stride
			(void*)(0)          // array buffer offset
	);


    glGenBuffers(1, &tex_uv);
    glBindBuffer(GL_ARRAY_BUFFER, tex_uv);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tri_uv), tri_uv, GL_STATIC_DRAW);
	
    glEnableVertexAttribArray(1);
	glVertexAttribPointer(
			1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			2,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,  // stride
			(void*)(0)          // array buffer offset
	);

    //unbind();

    // glEnableVertexAttribArray(2);
    // glVertexAttribPointer(
	// 	2,
	// 	3,
	// 	GL_FLOAT,
	// 	GL_FALSE,
	// 	3 * sizeof(float),
	// 	(void*)(3 * sizeof(float))
	// );

	//texture = load_texture("./img/wall.jpg");
}

GLuint RMeshTriangle::get_index_count() const {
    return 3;
}

void RMeshTriangle::bind() const {
	//glBindTexture(GL_TEXTURE_2D, texture);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_tri);
}

void RMeshTriangle::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindTexture(GL_TEXTURE_2D, 0);
}

void RMeshTriangle::cleanup() const {
    
}