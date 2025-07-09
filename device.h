#pragma once


#include <map>
#include <memory>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>


class Input;
struct Timer;
class VideoDriver;

class Device {
public:

	bool run();

	std::unique_ptr<VideoDriver> getVideoDriver();
	std::unique_ptr<Timer> getTimer();

	void window_swap();
	void poll_events();

	void set_input(Input* in);

	void set_window(GLFWwindow* win);
	GLFWwindow* get_window();

private:
	GLFWwindow* window;
	Input* input;	
};

std::unique_ptr<Device> makeDevice(int screen_w, int screen_h);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void cursor_position_callback(GLFWwindow* window, double  xpos, double ypos);
static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);