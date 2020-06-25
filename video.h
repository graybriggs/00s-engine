#pragma once


#include <glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GLFW/glfw3.h>


class VideoDriver {
public:

	void beginScene();
	void endScene();

	void drawAll();

public:

	GLFWwindow* window; // GET RID OF THIS SOMEHOW

};

