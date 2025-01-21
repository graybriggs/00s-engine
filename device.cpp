
#include "device.h"
#include "video.h"

#include <exception>
#include <string>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>


#include "timer.h"

bool Device::run() {
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0)
		return true;

	return false;
}


std::unique_ptr<VideoDriver> Device::getVideoDriver() {
	
	auto video = std::make_unique<VideoDriver>();
	return video;
}

std::unique_ptr<Timer> Device::getTimer() {

	auto timer = std::make_unique<Timer>();

	return timer;
}


std::unique_ptr<Device> makeDevice(int screen_w, int screen_h) {

	auto device = std::make_unique<Device>();

	glewExperimental = true; // Needed for core profile
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		//throw std::exception("blah");  // constructor of std::exception does not take a c string as an argument.
		// This must have worked before because of a non-standard, non-portable extension in visual studio
	}
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	
	device->window = glfwCreateWindow(screen_w, screen_h, "ogl", NULL, NULL);
	if (device->window == NULL) {
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		//throw std::exception("failed to open GLFW window.");
	}
	glfwMakeContextCurrent(device->window); // Initialize GLEW
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		//throw std::exception("failed to initialize glew");
	}

	return device;
}

void Device::window_swap() {
	glfwSwapBuffers(window);
}

void Device::poll_events() {
	glfwPollEvents();
}