#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>


#include <memory>


class VideoDriver;
struct Timer;

class Device {
public:

	bool run();

	std::unique_ptr<VideoDriver> getVideoDriver();
	std::unique_ptr<Timer> getTimer();

	void window_swap();
	void poll_events();


public:
	GLFWwindow* window;

};

std::unique_ptr<Device> makeDevice(int screen_w, int screen_h);