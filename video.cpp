
#include "video.h"


#include <glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GLFW/glfw3.h>

void VideoDriver::beginScene() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void VideoDriver::endScene() {

	glfwSwapBuffers(window);
	glfwPollEvents(); // MOVE THIS OUT
}

void VideoDriver::drawAll() {

}