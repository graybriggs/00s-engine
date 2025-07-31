#include <cstdio>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include "material.h"

void Material::add_shader(const std::string& name, Shader* sh) {
	shaders[name] = sh;
}

Shader* Material::get_shader(const std::string& name) {

	 return shaders[name];
}

Shader* Material::get_shader_from_material(MaterialType type) {
	
// 	switch (type) {
// 		case MaterialType::Color:
// 			return 
// 	}
	return nullptr;
}