#pragma once

#include <glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GLFW/glfw3.h>


#include <memory>


class VideoDriver;
struct Timer;

class Device {
public:

	bool run();

	std::unique_ptr<VideoDriver> getVideoDriver();
	std::unique_ptr<Timer> getTimer();


public:
	GLFWwindow* window;

};

std::unique_ptr<Device> makeDevice(int screen_w, int screen_h);