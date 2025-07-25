
#include "config.h"
#include "device.h"
#include "input.h"
#include "key.h"
#include "timer.h"
#include "video.h"

#include <exception>
#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>


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


	
	GLFWwindow* window = glfwCreateWindow(screen_w, screen_h, "Rendering Engine", nullptr, nullptr);
	device->set_window(window);
	if (device->get_window() == nullptr) {
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		//throw std::exception("failed to open GLFW window.");
	}
	glfwMakeContextCurrent(device->get_window()); // Initialize GLEW
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		//throw std::exception("failed to initialize glew");
	}

	//glfwSetInputMode(device->get_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//glfwSetInputMode(device->get_window(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	//glfwSetInputMode(device->get_window(), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	glfwSetInputMode(device->get_window(), GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetKeyCallback(device->get_window(), key_callback);
	glfwSetCursorPosCallback(device->get_window(), cursor_position_callback);
	glfwSetMouseButtonCallback(device->get_window(), mouse_button_callback);

	return device;
}

void Device::window_swap() {
	glfwSwapBuffers(window);
}

void Device::poll_events() {
	glfwPollEvents();
}

void Device::set_input(Input* in) {
	//input = in;

	glfwSetWindowUserPointer(window, static_cast<void*>(in));
}

void Device::set_window(GLFWwindow* win) {
	window = win;
}

GLFWwindow* Device::get_window() {
	return window;
}

void Device::set_window_name(const std::string& name) {
	glfwSetWindowTitle(get_window(), name.c_str());
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		input->key[static_cast<int>(Key::KeyPress::W)] = true;
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		input->key[static_cast<int>(Key::KeyPress::A)] = true;
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		input->key[static_cast<int>(Key::KeyPress::S)] = true;
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		input->key[static_cast<int>(Key::KeyPress::D)] = true;
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		input->key[static_cast<int>(Key::KeyPress::UP)] = true;
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		input->key[static_cast<int>(Key::KeyPress::DOWN)] = true;
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
		input->key[static_cast<int>(Key::KeyPress::LEFT)] = true;
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		input->key[static_cast<int>(Key::KeyPress::RIGHT)] = true;
	}


	if (key == GLFW_KEY_W && action == GLFW_RELEASE) {
		input->key[static_cast<int>(Key::KeyPress::W)] = false;
	}
	if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
		input->key[static_cast<int>(Key::KeyPress::A)] = false;
	}
	if (key == GLFW_KEY_S && action == GLFW_RELEASE) {
		input->key[static_cast<int>(Key::KeyPress::S)] = false;
	}
	if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
		input->key[static_cast<int>(Key::KeyPress::D)] = false;
	}
	if (key == GLFW_KEY_UP && action == GLFW_RELEASE) {
		input->key[static_cast<int>(Key::KeyPress::UP)] = false;
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) {
		input->key[static_cast<int>(Key::KeyPress::DOWN)] = false;
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) {
		input->key[static_cast<int>(Key::KeyPress::LEFT)] = false;
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) {
		input->key[static_cast<int>(Key::KeyPress::RIGHT)] = false;
	}
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));
	
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	input->set_mouse_cursor(x, y);
	//printf("x: %f y: %f\n", x, y);
	
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	//width = config::SCREEN_W;
	//height = config::SCREEN_H;
	//std::cout << "Window w/h: " << width << ", " << height << "\n";
	glfwSetCursorPos(window, width / 2, height / 2);
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		//printf("%i %i %i\n", button, action, mods);
		input->set_left_mouse_click();
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		input->set_left_mouse_release();
	}
}