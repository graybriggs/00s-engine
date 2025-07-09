#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "drawable.h"

class Triangle : public Drawable {
public:
	GLuint prepare_vertex_data() override {
		static const GLfloat triBufferData[] = {
			-1.0f, -1.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
		};

		GLuint vertexbuffertri;
		glGenBuffers(1, &vertexbuffertri);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffertri);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triBufferData), triBufferData, GL_STATIC_DRAW);

		return vertexbuffertri;
	}


	GLuint prepare_color_data() override {
		static const GLfloat tri_color_data[] = {
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f,
		};

		GLuint buffer;
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(tri_color_data), tri_color_data, GL_STATIC_DRAW);

		return buffer;
	}
	   


};