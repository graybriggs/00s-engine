
#include <iostream>
#include <cmath>
#include <map>
#include <memory>
#include <vector>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>

#include "camera.h"
#include "composite_entity.h"
#include "config.h"
#include "device.h"
#include "entity.h"
#include "input.h"
#include "key.h"
#include "light.h"
#include "material.h"
#include "./mesh/renderable_mesh.h"
#include "./mesh/mesh_cube.h"
#include "mesh_data.h"
#include "./mesh/mesh_line.h"
#include "./mesh/mesh_model.h"
#include "./mesh/mesh_quad.h"
#include "./mesh/mesh_triangle.h"
#include "model_loader.h"
#include "ray.h"
#include "scene.h"
#include "selection_axis.h"
#include "shader.h"
#include "texture.h"
#include "texture_loader.h"
#include "timer.h"
#include "toggle.h"
#include "video.h"

#include "./util/array2d.h"
#include "./math/normal_generator.h"

#include "heightmap.h"
#include "terrain_data.h"
#include "mesh_terrain.h"

int main() {

	auto device = makeDevice(config::SCREEN_W, config::SCREEN_H);
	auto input = std::make_unique<Input>();
	device->set_input(input.get());
	auto video = device->getVideoDriver();

	////////////////////////////

	video->setup();

	/////////////////////////////
	 Shader color_shader("./shaders/vs_color.vert", "./shaders/fs_color.frag");
	 Shader diffuse_shader("./shaders/vs_diffuse.vert", "./shaders/fs_diffuse.frag");
	 Shader texture_shader("./shaders/vs_texture.vert", "./shaders/fs_texture.frag");
	 Shader terrain_shader("./shaders/vs_terrain.vert", "./shaders/fs_terrain.frag");
	 Shader normals_shader("./shaders/vs_normals.vert", "./shaders/fs_normals.frag", "./shaders/gs_normals.geom");

	 Material new_material;
	 new_material.add_shader("color", &color_shader);
	 new_material.add_shader("diffuse", &diffuse_shader);
	 new_material.add_shader("texture", &texture_shader);
	 new_material.add_shader("terrain", &terrain_shader);
	 new_material.add_shader("normals", &normals_shader);

	const auto tri_mesh = std::make_unique<RMeshTriangle>();
	const auto quad_mesh = std::make_unique<RMeshQuad>();
	const auto cube_mesh = std::make_unique<RMeshCube>();
	const auto line_mesh = std::make_unique<RMeshLine>();
	
	TextureManager tm;
	Texture box_tex(tm.load_texture("thing", "./img/thing.jpg"));
	Texture wall_tex(tm.load_texture("wall", "./img/wall.jpg"));

	Entity e1(cube_mesh.get(), new_material, box_tex, EntityType::TEXTURED_MODEL);
	e1.scale(glm::vec3(3,3,3));
	e1.translate(glm::vec3(0.0, 3.0, -6.0));
	
	Entity e2(tri_mesh.get(), new_material, wall_tex, EntityType::TEXTURED_MODEL);
	e2.scale(glm::vec3(4.0,4.0,4.0));
	e2.translate(glm::vec3(6.0, 5.0, 4.0));

	Entity e3(quad_mesh.get(), new_material, box_tex, EntityType::TEXTURED_MODEL);
	e3.scale(glm::vec3(5,5,5));
	e3.translate(glm::vec3(4.0, 4.0, 3.0));
	
	Entity e4(tri_mesh.get(), new_material, box_tex, EntityType::TEXTURED_MODEL);
	e4.scale(glm::vec3(3.0, 3.0, 3.0));
	//e4.rotate(glm::radians(-45.0f), glm::vec3(0.0, 1.0, 0.0));
	e4.translate(glm::vec3(4.0, 6.0, -2.0));

	Entity e5(quad_mesh.get(), new_material, box_tex, EntityType::TEXTURED_MODEL);
	e5.translate(glm::vec3(4.0, 4.0, -4.0));
	
	Entity e6(quad_mesh.get(), new_material, wall_tex, EntityType::TEXTURED_MODEL);
	e6.translate(glm::vec3(-6.0, 2.0, -2.0));
	
	Entity e7(quad_mesh.get(), new_material, box_tex, EntityType::TEXTURED_MODEL);
	//e7.scale(glm::vec3(8,8,8));
	//e7.rotate(glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	e7.translate(glm::vec3(0.0, 2.0, 0.0));
	
	Entity e8(line_mesh.get(), new_material, 0, EntityType::LINE);
	e8.scale(glm::vec3(0.5f, 0.5f, 0.5f));
	e8.rotate(glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	e8.translate(glm::vec3(0.0, 6.0, 0.0));

	Entity e9(cube_mesh.get(), new_material, box_tex, EntityType::TEXTURED_MODEL);
	//e9.scale(glm::vec3(2.0, 2.0, 2.0));
	e9.translate(glm::vec3(0.0, 3.0, -20.0));

	Scene scene;
	scene.add_entity(&e1);
	scene.add_entity(&e2);
	scene.add_entity(&e3);
	scene.add_entity(&e4);
	scene.add_entity(&e5);
	scene.add_entity(&e6);
	scene.add_entity(&e7);
	//scene.add_entity(&e8);
	scene.add_entity(&e9);
	


	constexpr int CUBE_MAX = 4096;
	constexpr float offset = 32.0f;
	constexpr float step = 1.0f;
	float x = -offset;
	float z = -offset;
	float y = -180.0f;
	for (int i = 0; i < CUBE_MAX; ++i) {
		Entity* e = new Entity(cube_mesh.get(), new_material, wall_tex, EntityType::TEXTURED_MODEL);
		glm::vec3 bp(x, 10 * glm::sin(glm::radians(y)), z);
		e->translate(bp);
		e->set_base_position(bp);
		scene.add_entity(e);
		x += step;
		if (x >= offset) {
			x = -offset;
			z += step;
			y += 1.0f / 360.0f;
		}
	}

	// MeshData sphere_mesh_data;
	// if (!load_obj("./models/cube.obj", sphere_mesh_data)) {
	// 	std::cerr << "Model load failed.\n";
	// }
	// auto sphere_mesh = std::make_unique<RMeshModel>(sphere_mesh_data);
	// Entity ent_sphere(sphere_mesh.get(), diffuse_material, 0, EntityType::UNTEXTURED_MODEL);
	// //ent_teapot.rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	// ent_sphere.scale(glm::vec3(5.0f, 5.0f, 5.0f));
	// ent_sphere.translate(glm::vec3(-2.0f, 2.0f, -1.0f));
	// scene.add_entity(&ent_sphere);

	// MeshData suzanne_mesh_data;
	// if (!load_obj("./models/suzanne.obj", suzanne_mesh_data)) {
	// 	std::cerr << "Model load failed.\n";
	// }
	// auto suzanne_mesh = std::make_unique<RMeshModel>(suzanne_mesh_data);
	// Entity ent_suzanne(suzanne_mesh.get(), diffuse_material, 0, EntityType::UNTEXTURED_MODEL);
	// ent_suzanne.scale(glm::vec3(5.0f, 5.0f, 5.0f));
	// ent_suzanne.translate(glm::vec3(5.0, 1.0, -3.0));
	// scene.add_entity(&ent_suzanne);

	// MeshData teapot_mesh_data;
	// if (!load_obj("./models/teapot.obj", teapot_mesh_data)) {
	// 	std::cerr << "Model load failed.\n";
	// }
	// auto teapot_mesh = std::make_unique<RMeshModel>(teapot_mesh_data);
	// Entity ent_teapot(teapot_mesh.get(), texture_material, 0, EntityType::UNTEXTURED_MODEL);
	// ent_teapot.scale(glm::vec3(2.0f, 2.0f, 2.0f));
	// ent_teapot.translate(glm::vec3(-20.0, 0.0, -15.0));
	// scene.add_entity(&ent_teapot);


	// auto light_mesh = std::make_unique<RMeshCube>();
	// Entity ent_light(light_mesh.get(), color_material, 0, EntityType::LIGHT);
	// ent_light.set_viewable_flag(false);
	// scene.add_entity(&ent_light);

	Light light(new_material, glm::vec3(0,0,0));
	light.translate(glm::vec3(5.0f, 15.0f, 0.0f));
	light.set_color(glm::vec3(0.0, 0.0, 1.0));
	scene.add_light(&light);

	////////////////

	auto camera = Camera(
		{0, 0, -5}, // pos
		{0, 0, 0}, // lookat
		{0, 1, 0}, // up
		config::SCREEN_W,
		config::SCREEN_H,
		0.1f,
		2000.0f
	);
	camera.set_velocity(0.8f);
	camera.set_input(input.get());

	glm::vec3 cam_velocity(0.0f, 0.0f, 0.0f);

// ------------

	HeightMapImageData hid;
	load_heightmap("./img/iceland_heightmap.png", hid);
	TerrainData td;
	td.min_x = -hid.width / 2.0f;
	td.min_z = -hid.height / 2.0f;
	td.cell_width = 1;
	td.cell_height = 1;
	std::cout << "height: " << hid.height << ", width: " << hid.width << "\n";
	td.vertices = generate_vertices(hid);
	td.indices = generate_indices(hid);
	RMeshTerrain rmt(td);
	TerrainRenderData trd;
	process_heightmap(hid, trd);



// -------------

	SelectionAxis selection_axis(cube_mesh.get(), new_material);
	scene.add_composite_entity(selection_axis.get_selection_axis_composite());

// -------


	Timer timer;
	//timer.start_timer();
	//double frame_start = timer.current_time();
	double accumulator = 0.0;
	double delta = 1.0 / config::FPS;
	
	double val = 1.0;


	Toggles toggles;


	while (device->run()) {
		
		
		timer.start_frame_time();
		timer.check_frame_time();


		// double current_time = timer.current_time();
		// double delta = current_time - frame_start;
		// frame_start = current_time;
		
		device->poll_events();

		check_toggle_key(input.get(), toggles);

		// RED - x
		// GREEN - y
		// BLUE - z

		if (toggles.edit_mode) {
			if (input->get_left_mouse_button_state()) {
				auto cursor = input->get_cursor_pos();
				auto ray = cast_ray(cursor, camera.get_projection(), camera.get_view());
				ray.origin = glm::vec4(camera.get_camera_position(), 1.0);

				auto axis = selection_axis.get_selection_axis_composite();
				auto children = axis->get_children();
				int count = 0;
				for (auto child : children) {
					Sphere axis_sphere;
					axis_sphere.center_position = child->get_3d_coords();
					axis_sphere.radius = 2.0f;
					bool b = ray_intersect_sphere(ray, axis_sphere);
					//std::cout << "T/F: " << b << std::endl;
					if (b) {
						// if (child->get_base_color() == 3) {
						// 	std::cout << "intersection on WHITE" << std::endl;
						// }
						// if (child->get_base_color() == 0)
						// 	std::cout << "Found x axis\n";
						// if (child->get_base_color() == 1)
						// 	std::cout << "Found y axis\n";
						// if (child->get_base_color() == 2)
						// 	std::cout << "Found z axis\n";
						std::cout << "Count: " << count << std::endl;
					}
					++count;
				}

				// get selection_axis children
				// if ray is intersecting
				// while mouse being held
				// move along that child's axis
			}
		}


		if (!toggles.edit_mode && input->get_left_mouse_button_state()) {
			auto cursor = input->get_cursor_pos();
			//std::cout << "Cursor: " << cursor.xpos << ", " << cursor.ypos << "\n";
			auto ray = cast_ray(cursor, camera.get_projection(), camera.get_view());
			ray.origin = glm::vec4(camera.get_camera_position(), 1.0);
			//std::cout << r.x << ", " << r.y << ", " << r.z << std::endl;

			int count = 0;
			for (auto entity : scene.get_entities()) {
				Sphere sphere;
				sphere.center_position = entity->get_3d_coords();
				sphere.radius = 0.5f;
				
				bool b = ray_intersect_sphere(ray, sphere);
				if (b) {
					std::cout << "Cube " << count << " Intersection\n";
					entity->set_highlight(true);
					glm::mat4 res(1.0);
					float space = 1.0f;
					sphere.center_position.y += space;
					res = glm::translate(res, sphere.center_position);
					//composite_axis.set_model_matrix(res);
					selection_axis.set_model_matrix(res);
					break;
				}
				++count;
				// bool q = ray_intersect_sphere(camera.get_camera_position(), r, glm::vec3(0.0, 2.0, 0.0), 1.0f);
				// if (q) {
				// 	std::cout << "Quad Intersection\n";
				// }
			}
		}
		if (input->get_right_mouse_button_state()) {
			for (auto entity : scene.get_entities()) {
				if (entity->get_highlight()) {
					entity->set_highlight(false);
				}
			}
		}
	

		if (toggles.terrain_edit) {
			if (input->get_left_mouse_button_state()) {
				auto cursor = input->get_cursor_pos();
				auto ray = cast_ray(cursor, camera.get_projection(), camera.get_view());
				ray.origin = glm::vec4(camera.get_camera_position(), 1.0);
			}

			//auto res = ray_intersect_terrain(ray, )
		}


		// scene.entities[2]->rotate(glm::radians(val), glm::vec3(1.0,1.0,1.0));
		// scene.entities[scene.entities.size()-3]->rotate(glm::radians(glm::sin(val-1.5f)), glm::vec3(0.0,1.0,0.0));
		// scene.entities[scene.entities.size()-2]->rotate(glm::radians(val), glm::vec3(0.0,1.0,0.0));

		camera.update(delta);

		// Within a bounds in front of the camera
		glm::vec3 pos = camera.get_camera_position();
		glm::vec3 dir = camera.calculate_direction();

		constexpr float unit_distance = 20.0f;
		glm::vec3 upper_left = glm::vec3(dir.x + pos.x, pos.y, dir.z * unit_distance + pos.z);
		glm::vec3 lower_right = glm::vec3(dir.x * unit_distance + pos.x, pos.y, dir.z + pos.z);



		
		video->begin_scene();
		
		video->draw_fill();
		video->light_renderer(camera, scene);
		
		video->entity_renderer(camera, scene);
		if (toggles.display_normals) {
			Shader* sh = new_material.get_shader("normals");
			video->entity_renderer(camera, scene, sh);
		}
		
		video->composite_entity_renderer(camera, scene);
		
		input->update();
		if (toggles.wireframe) {
			video->draw_lines();
		}
		//video->draw_points();
		video->terrain_renderer(camera, &rmt, trd, new_material);
		
		video->end_scene();
		
		device->window_swap();
	}

	for (auto e : scene.entities) {
		e->get_mesh()->cleanup();
	}
}