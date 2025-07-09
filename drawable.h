#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>


class Drawable {
public:

	virtual ~Drawable() = default;

	virtual GLuint prepare_vertex_data() = 0;
	virtual GLuint prepare_color_data() = 0;

private:

};