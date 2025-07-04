#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include "mesh_cube.h"
#include "stb_image.h"


RMeshCube::RMeshCube() {

	constexpr int CUBE_BUFFER_SIZE = 36 * 3;

	const GLfloat cube_data[CUBE_BUFFER_SIZE] = {
		// -1.0f,-1.0f,-1.0f, 
		// -1.0f,-1.0f, 1.0f,
		// -1.0f, 1.0f, 1.0f, 
		// 1.0f, 1.0f,-1.0f, 
		// -1.0f,-1.0f,-1.0f,
		// -1.0f, 1.0f,-1.0f, 

		// 1.0f,-1.0f, 1.0f,
		// -1.0f,-1.0f,-1.0f,
		// 1.0f,-1.0f,-1.0f,
		// 1.0f, 1.0f,-1.0f,
		// 1.0f,-1.0f,-1.0f,
		// -1.0f,-1.0f,-1.0f, 

		// -1.0f,-1.0f,-1.0f,
		// -1.0f, 1.0f, 1.0f,
		// -1.0f, 1.0f,-1.0f,
		// 1.0f,-1.0f, 1.0f,
		// -1.0f,-1.0f, 1.0f,
		// -1.0f,-1.0f,-1.0f,

		// -1.0f, 1.0f, 1.0f,
		// -1.0f,-1.0f, 1.0f,
		// 1.0f,-1.0f, 1.0f,
		// 1.0f, 1.0f, 1.0f,
		// 1.0f,-1.0f,-1.0f,
		// 1.0f, 1.0f,-1.0f,

		// 1.0f,-1.0f,-1.0f,
		// 1.0f, 1.0f, 1.0f,
		// 1.0f,-1.0f, 1.0f,
		// 1.0f, 1.0f, 1.0f,
		// 1.0f, 1.0f,-1.0f,
		// -1.0f, 1.0f,-1.0f,

		// 1.0f, 1.0f, 1.0f,
		// -1.0f, 1.0f,-1.0f,
		// -1.0f, 1.0f, 1.0f,
		// 1.0f, 1.0f, 1.0f,
		// -1.0f, 1.0f, 1.0f,
		// 1.0f,-1.0f, 1.0f
		    // Front face
    -0.5f, -0.5f,  0.5f,     // Bottom-left
     0.5f, -0.5f,  0.5f,     // Bottom-right
     0.5f,  0.5f,  0.5f,     // Top-right
    -0.5f,  0.5f,  0.5f,     // Top-left

    // Back face
    -0.5f, -0.5f, -0.5f,   
     0.5f, -0.5f, -0.5f,   
     0.5f,  0.5f, -0.5f,   
    -0.5f,  0.5f, -0.5f,   

    // Left face
    -0.5f, -0.5f, -0.5f,   
    -0.5f, -0.5f,  0.5f,   
    -0.5f,  0.5f,  0.5f,   
    -0.5f,  0.5f, -0.5f,   

    // Right face
     0.5f, -0.5f, -0.5f,   
     0.5f, -0.5f,  0.5f,   
     0.5f,  0.5f,  0.5f,   
     0.5f,  0.5f, -0.5f,   

    // Top face
    -0.5f,  0.5f,  0.5f,   
     0.5f,  0.5f,  0.5f,   
     0.5f,  0.5f, -0.5f,   
    -0.5f,  0.5f, -0.5f,   

    // Bottom face
    -0.5f, -0.5f,  0.5f,   
     0.5f, -0.5f,  0.5f,   
     0.5f, -0.5f, -0.5f,   
    -0.5f, -0.5f, -0.5f   
	};

	// const GLfloat cube_color[CUBE_BUFFER_SIZE] = {
	// 	0.0f, 1.0f, 0.0f,
	// 	1.0f, 1.0f, 0.0f,
	// 	1.0f, 0.0f, 0.0f,
	// 	1.0f, 0.0f, 0.0f,
	// 	0.0f, 1.0f, 1.0f,
	// 	0.0f, 1.0f, 0.0f,

	// 	0.0f, 1.0f, 0.0f,
	// 	1.0f, 1.0f, 1.0f,
	// 	0.0f, 1.0f, 0.0f,
	// 	0.0f, 1.0f, 0.0f,
	// 	0.0f, 1.0f, 1.0f,
	// 	1.0f, 1.0f, 0.0f,

	// 	0.0f, 1.0f, 0.0f,
	// 	0.0f, 1.0f, 0.0f,
	// 	0.0f, 1.0f, 0.0f,
	// 	0.0f, 1.0f, 0.0f,
	// 	0.0f, 1.0f, 0.0f,
	// 	0.0f, 1.0f, 0.0f,

	// 	0.0f, 1.0f, 0.0f,
	// 	0.0f, 0.0f, 0.0f,
	// 	0.0f, 1.0f, 0.0f,
	// 	0.0f, 0.0f, 0.0f,
	// 	0.0f, 1.0f, 0.0f,
	// 	0.0f, 1.0f, 0.0f,

	// 	0.0f, 1.0f, 0.0f,
	// 	1.0f, 1.0f, 0.0f,
	// 	0.0f, 1.0f, 0.0f,
	// 	1.0f, 1.0f, 0.0f,
	// 	0.0f, 1.0f, 0.0f,
	// 	1.0f, 1.0f, 0.0f,

	// 	0.0f, 1.0f, 1.0f,
	// 	0.0f, 1.0f, 0.0f,
	// 	0.0f, 1.0f, 1.0f,
	// 	0.0f, 1.0f, 0.0f,
	// 	0.0f, 1.0f, 1.0f,
	// 	0.0f, 1.0f, 0.0f,
	// };

	const GLfloat tex_coords[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f
	};

	//GLuint indices[] = {
	std::vector<GLuint> idx = {
		0, 1, 2,  2, 3, 0,        // Front
		4, 5, 6,  6, 7, 4,        // Back
		8, 9,10, 10,11, 8,        // Left
		12,13,14, 14,15,12,        // Right
		16,17,18, 18,19,16,        // Top
		20,21,22, 22,23,20         // Bottom
	};
	indices = std::move(idx);

    glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
    
	glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_data), cube_data, GL_STATIC_DRAW);
	
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	glEnableVertexAttribArray(0);

    // glGenBuffers(1, &vbo_col);
    // glBindBuffer(GL_ARRAY_BUFFER, vbo_col);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(cube_color), cube_color, GL_STATIC_DRAW);

	// glEnableVertexAttribArray(1);
	// glVertexAttribPointer(
	// 		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	// 		3,                  // size
	// 		GL_FLOAT,           // type
	// 		GL_FALSE,           // normalized?
	// 		0,                  // stride
	// 		(void*)0            // array buffer offset
	// );


	glGenBuffers(1, &tex_uv);
	glBindBuffer(GL_ARRAY_BUFFER, tex_uv);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tex_coords), tex_coords, GL_STATIC_DRAW);

	glVertexAttribPointer(
		1,                  // attribute 0. 
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);

}

GLuint RMeshCube::get_index_count() const {
	// strictly, a range check is needed here since std::size_t is guaranteed to represent
	// the size of any object in memory (64bit) whereas GLuint is typically a 32-bit unsigned integer
	// eg.,
	// std::size_t size = container.size();
	// if (size > std::numeric_limits<GLuint>::max())
	//   throw ...
	// }
	//
	// static_cast with caution

	return static_cast<GLuint>(indices.size());
}

void RMeshCube::bind() const {
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

void RMeshCube::unbind() const {
	glBindVertexArray(0);
}

void RMeshCube::cleanup() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}