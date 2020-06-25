#pragma once

#include <glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GLFW/glfw3.h>

#include <string>

class Drawable {
public:

	virtual ~Drawable() = default;

	virtual GLuint prepare_vertex_data() = 0;
	virtual GLuint prepare_color_data() = 0;

private:

};