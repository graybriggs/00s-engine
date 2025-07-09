#pragma once

#include <vector>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "camera.h"
#include "scene.h"

class VideoDriver {
public:

	void setup();

	void begin_scene();
	void end_scene();

	void renderer(const Camera& camera, const Scene& scene);

private:

};

