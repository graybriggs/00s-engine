#pragma once
#ifndef SHAPEGENERATOR_H
#define SHAPEGENERATOR_H

#include <glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "vertex.h"

struct ShapeData {
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
};

class ShapeGenerator {

	static ShapeData makePlaneVerts(int dimensions);
	static ShapeData makePlaneIndices(int dimensons);

public:

	static ShapeData makeTriangle();
	static ShapeData makeRectangle();
	static ShapeData makeQuad();
	static ShapeData makeCube();
	static ShapeData makePlane(int dimensions, GLfloat step = 1.0f);
	static ShapeData makeModel(const char* path);

	static std::vector<GLfloat> extractVertices(const std::vector<Vertex>& vertices);
	static std::vector<GLfloat> extractColors(const std::vector<Vertex>& colors);
};


#endif
