#pragma once

#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

//#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GLFW/glfw3.h>

struct MeshData {

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	std::vector<GLuint> vertex_indices;
	std::vector<GLuint> uv_indices;
	std::vector<GLuint> normal_indices;

};