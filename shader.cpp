
#include "shader.h"

#include "texture.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> 


Shader::Shader(const char* vs_path, const char* fs_path):
	geometry_id(-1) {

	auto vsc = load_shader(vs_path);
	compile_shader(vsc, ShaderType::VERTEX);
	auto fsc = load_shader(fs_path);
	compile_shader(fsc, ShaderType::FRAGMENT);
	link_shader();
	cleanup_shader();
}

Shader::Shader(const char* vs_path, const char* fs_path, const char* gs_path) {

	auto vsc = load_shader(vs_path);
	compile_shader(vsc, ShaderType::VERTEX);
	auto fsc = load_shader(fs_path);
	compile_shader(fsc, ShaderType::FRAGMENT);
	auto gsc = load_shader(gs_path);
	compile_shader(gsc, ShaderType::GEOMETRY);
	link_shader();
	cleanup_shader();
}

void Shader::use_program() {
	glUseProgram(program_id);
}

GLuint Shader::get_program() const {
	return program_id;
}

void Shader::set_uniform(std::string id, glm::vec3 v3) {
	GLuint uniform_location = glGetUniformLocation(program_id, id.c_str());
	glUniform3fv(uniform_location, 1, glm::value_ptr(v3));
}

void Shader::set_uniform(std::string id, glm::mat4 m4) {
	GLuint uniform_location = glGetUniformLocation(program_id, id.c_str());
	glUniformMatrix4fv(uniform_location, 1, GL_FALSE, glm::value_ptr(m4));
}

void Shader::set_texture(std::string name, Texture texture, GLenum texture_unit) {
	auto texture_id = texture.get_id();
	glActiveTexture(texture_unit);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	//GLuint texture_sampler = glGetUniformLocation(program_id, "tex_sampler0");
	GLuint texture_sampler = glGetUniformLocation(program_id, name.c_str());
	glUniform1i(texture_sampler, 0);
}

////
// private methods
///

std::string Shader::load_shader(const std::string path) {
	// read from file
	shader_from_path = path;
	std::string shader_code;
	std::ifstream shader_stream(path.c_str(), std::ios::in);
	if (shader_stream.is_open()) {
		std::stringstream sstr;
		sstr << shader_stream.rdbuf();
		shader_code = sstr.str();
		shader_stream.close();
		return shader_code;
	}
	else {
		std::cout << "Cannot open: " << path << "\n";
		//getchar();
		//return 0;
		throw std::runtime_error("Cannot open: " + std::string(path));
	}
}

void Shader::compile_msg(GLuint id) {
	std::cerr << "Compiling shader: " << shader_from_path << "Shader [#" << id << "]\n";
}

void Shader::compile_shader(const std::string& shader_code, ShaderType type) {

	
	char const* source_ptr = shader_code.c_str();
	
	if (type == ShaderType::VERTEX) {
		vertex_id = glCreateShader(GL_VERTEX_SHADER);
		compile_msg(vertex_id);
		glShaderSource(vertex_id, 1, &source_ptr, nullptr);
		glCompileShader(vertex_id);
		post_compile_check(vertex_id, ShaderType::VERTEX);
	}
	else if (type == ShaderType::GEOMETRY) {
		geometry_id = glCreateShader(GL_GEOMETRY_SHADER);
		compile_msg(geometry_id);
		glShaderSource(geometry_id, 1, &source_ptr, nullptr);
		glCompileShader(geometry_id);
		post_compile_check(geometry_id, ShaderType::GEOMETRY);
	}
	else if (type == ShaderType::FRAGMENT) {
		fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
		compile_msg(fragment_id);
		glShaderSource(fragment_id, 1, &source_ptr, nullptr);
		glCompileShader(fragment_id);
		post_compile_check(fragment_id, ShaderType::FRAGMENT);
	}
	
	
}

void Shader::post_compile_check(GLuint shader_type, ShaderType type) {
	GLint success = GL_FALSE;
	int log_length;

	glGetShaderiv(shader_type, GL_COMPILE_STATUS, &success);
	glGetShaderiv(shader_type, GL_INFO_LOG_LENGTH, &log_length);
	if (!success) {
		std::vector<char> error_message(log_length + 1);
		glGetShaderInfoLog(shader_type, log_length, nullptr, error_message.data());

		std::string str;
		if (type == ShaderType::VERTEX) str = "Vertex Shader";
		else if (type == ShaderType::GEOMETRY) str = "Geometry Shader";
		else if (type == ShaderType::FRAGMENT) str = "Fragment Shader";
		else str = "No type";
		
		std::cout << "MESSAGE SIZE: " << error_message.size() << error_message[0] << "\n";
		std::cerr << "ERROR: [" << shader_type << "] " << str << " - ShaderInfoLog(compile): " << error_message.data() << "\n";
	}
	else {
		std::cout << "Shader: " << shader_type << " compiled OK\n";
	}
}

void Shader::link_shader() {

	std::cout << "Linking material program\n";

	program_id = glCreateProgram();
	glAttachShader(program_id, vertex_id);
	glAttachShader(program_id, fragment_id);

	if (geometry_id > 0) {
		glAttachShader(program_id, geometry_id);
	}

    glLinkProgram(program_id);
    
	GLint result = GL_FALSE;
	int info_log_length;

	glGetProgramiv(program_id, GL_LINK_STATUS, &result);
	glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);
	if (info_log_length > 0) {
		std::vector<char> error_message(info_log_length + 1);
		glGetProgramInfoLog(program_id, info_log_length, nullptr, &error_message[0]);
		std::cerr << "ShaderInfoLog(linker): " << error_message.data() << "\n";
	}
	else {
		std::cout << "Shader: " << program_id << " linked OK\n";
	}
}

void Shader::cleanup_shader() {
	glDetachShader(program_id, vertex_id);
	glDetachShader(program_id, fragment_id);

	if (geometry_id > 0) {
		glDetachShader(program_id, geometry_id);
	}

	glDeleteShader(vertex_id);
	glDeleteShader(fragment_id);

	if (geometry_id > 0) {
		glDeleteShader(geometry_id);
	}
}
