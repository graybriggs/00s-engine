#pragma once

#include <string>
#include <vector>

#include <glm/vec3.hpp>

struct Vertex {
	GLfloat vert[3];
	GLfloat color[3];
	// texture
	// normal

	Vertex(GLfloat x, GLfloat y, GLfloat z) {
		vert[0] = x;
		vert[1] = y;
		vert[2] = z;
		color[0] = 0.0f;
		color[1] = 0.0f;
		color[2] = 0.0f;
	}

	Vertex(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b) {
		vert[0] = x;
		vert[1] = y;
		vert[2] = z;
		color[0] = r;
		color[1] = g;
		color[2] = b;
	}

	void setVertex(GLfloat x, GLfloat y, GLfloat z) {
		vert[0] = x;
		vert[1] = y;
		vert[2] = z;
	}

	void setColors(GLfloat r, GLfloat g, GLfloat b) {
		color[0] = r;
		color[1] = g;
		color[2] = b;
	}
};

/*
struct SimpleVertex {
	glm::vec3 vert;
	glm::vec3 color;
	glm::vec3 normal;
	glm::vec3 texcoord;
};
*/

struct VertexList {
	std::vector<Vertex> vertex_list; 
};
