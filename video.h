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
#include "terrain_data.h"

class RMeshTerrain;

class VideoDriver {
public:

	void setup();

	void begin_scene();
	void end_scene();

	void draw_points();
	void draw_lines();
	void draw_fill();

	void renderer(const Camera& camera, const Scene& scene);
	void terrain_renderer(const Camera& camera, const RMeshTerrain* rmt, const TerrainRenderData& trd, Material& mat);

private:

};

