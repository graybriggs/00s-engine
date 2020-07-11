

#include "shape_generator.h"

#include "vertex.h"

ShapeData ShapeGenerator::makeTriangle() {

	ShapeData shapeData;
	
	Vertex v1(-1.0f, -1.0f, 0.0f);
	Vertex v2(1.0f, -1.0f, 0.0f);
	Vertex v3(0.0f, 1.0f, 0.0f);
	
	v1.setColors(1.0f, 0.0f, 0.0f);
	v2.setColors(0.0f, 1.0f, 0.0f);
	v2.setColors(0.0f, 0.0f, 1.0f);

	shapeData.vertices.push_back(v1);
	shapeData.vertices.push_back(v2);
	shapeData.vertices.push_back(v3);
	
	return shapeData;
}

ShapeData ShapeGenerator::makeRectangle() {
	ShapeData shapeData;

	shapeData.vertices.push_back(Vertex(-1.0f, -1.0f, 0.0f));
	shapeData.vertices.push_back(Vertex( 1.0f, -1.0f, 0.0f));
	shapeData.vertices.push_back(Vertex(-1.0f, 1.0f, 0.0f));
	shapeData.vertices.push_back(Vertex(1.0f, 1.0f, 0.0f));

	shapeData.indices = std::vector<GLuint>{ 0, 1, 2, 3 };


	return shapeData;
}

ShapeData ShapeGenerator::makeQuad() {
	ShapeData shapeData;

	shapeData.vertices.push_back(Vertex(-1.0f, -1.0f, 0.0f));
	shapeData.vertices.push_back(Vertex(1.0f, -1.0f, 0.0f));
	shapeData.vertices.push_back(Vertex(1.0f, 1.0f, 0.0f));
	shapeData.vertices.push_back(Vertex(-1.0f, 1.0f, 0.0f));

	return shapeData;
}

ShapeData ShapeGenerator::makeCube() {

	constexpr int CUBE_BUFFER_SIZE = 36 * 3;

	const GLfloat vbd[CUBE_BUFFER_SIZE] = {
		-1.0f,-1.0f,-1.0f, // triangle 1 : begin
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, // triangle 1 : end
		1.0f, 1.0f,-1.0f, // triangle 2 : begin
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f, // triangle 2 : end
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};

	ShapeData shapeData;

	for (std::size_t i = 0; i < CUBE_BUFFER_SIZE; i += 3) {
		//Vertex v(vbd[i], vbd[i + 1], vbd[i + 2]);
		Vertex v(vbd[i], vbd[i + 1], vbd[i + 2], 1.0f, 0.0f, 0.0f);
		shapeData.vertices.push_back(v);
	}

	return shapeData;
}

ShapeData ShapeGenerator::makePlane(int dimensions, GLfloat step) {
	ShapeData shapeData;

	std::vector<Vertex> meshVertices;

	GLfloat x, y, z;
	x = y = -dimensions;
	z = 0.0f;

	for (int i = -dimensions; i < dimensions * dimensions - dimensions; ++i) {

		meshVertices.push_back(Vertex(x, y, z, 1.0f, 0.0f, 0.0f));

		if (x >= dimensions) {
			x = -dimensions;
			y += step;
		}
		else {
			x += step;
		}
	}

	shapeData.vertices = meshVertices;
	//shapeData.indices = // TODO

	return shapeData;
}

ShapeData ShapeGenerator::makeModel(const char* path) {
	ShapeData shapeData;
	// todo
	return shapeData;
}

std::vector<GLfloat> ShapeGenerator::extractVertices(const std::vector<Vertex>& vertices) {
	std::vector<GLfloat> verts;

	for (auto& v : vertices) {
		verts.push_back(v.vert[0]);
		verts.push_back(v.vert[1]);
		verts.push_back(v.vert[2]);
	}
	return verts;
}

std::vector<GLfloat> ShapeGenerator::extractColors(const std::vector<Vertex>& colors) {
	std::vector<GLfloat> cols;

	for (auto& c : colors) {
		cols.push_back(c.color[0]);
		cols.push_back(c.color[1]);
		cols.push_back(c.color[2]);
	}
	return cols;
}