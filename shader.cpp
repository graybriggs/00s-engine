
#include "shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>



GLuint load_shaders(const char* vertex_file_path, const char* fragment_file_path) {

	// Create the shaders
	GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else {
		printf("Cannot open %s\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}
	else {
		printf("Cannot open %s\n", fragment_file_path);
		getchar();
		return 0;
	}

	GLint result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(vertex_shader_id, 1, &VertexSourcePointer, NULL);
	glCompileShader(vertex_shader_id);

	// Check Vertex Shader
	glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(vertex_shader_id, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(fragment_shader_id, 1, &FragmentSourcePointer, NULL);
	glCompileShader(fragment_shader_id);

	// Check Fragment Shader
	glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragment_shader_id, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(fragment_shader_id, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint program_id = glCreateProgram();
	glAttachShader(program_id, vertex_shader_id);
	glAttachShader(program_id, fragment_shader_id);
	glLinkProgram(program_id);

	// Check the program
	glGetProgramiv(program_id, GL_LINK_STATUS, &result);
	glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(program_id, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(program_id,vertex_shader_id);
	glDetachShader(program_id, fragment_shader_id);

	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);

	return program_id;
}


Shader::Shader(const char* path, const ShaderType type) {

	// read from file
	std::string shader_code;
	std::ifstream shader_stream(path, std::ios::in);
	if (shader_stream.is_open()) {
		std::stringstream sstr;
		sstr << shader_stream.rdbuf();
		shader_code = sstr.str();
		shader_stream.close();
	}
	else {
		printf("Cannot open %s\n", path);
		getchar();
		//return 0;
		throw std::runtime_error("Cannot open: " + std::string(path));
	}

	shader_type = type;

	if (type == ShaderType::VERTEX) {
		shader_id = glCreateShader(GL_VERTEX_SHADER);
	}
	else if (type == ShaderType::GEOMETRY) {
		shader_id = glCreateShader(GL_GEOMETRY_SHADER);
	}
	else if (type == ShaderType::FRAGMENT) {
		shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	}

	printf("Compiling shader : %s\n", path);
	char const* source_ptr = shader_code.c_str();
	glShaderSource(shader_id, 1, &source_ptr, nullptr);
	glCompileShader(shader_id);

	// post compile check

	GLint result = GL_FALSE;
	int log_length;

	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);
	if (log_length > 0) {
		std::vector<char> error_message(log_length + 1);
		glGetShaderInfoLog(shader_id, log_length, nullptr, &error_message[0]);
		printf("ShaderInfoLog: %s\n", &error_message[0]);
	}

	std::cout << "Shader_id: " << shader_id << "\n";
}

GLuint Shader::handle() const {
	return shader_id;
}


// NEW

#include <iostream>



Shader_::Shader_(const char* vs_path, const char* fs_path) {

		load_shader(vs_path);
		compile_shader(ShaderType::VERTEX);
		load_shader(fs_path);
		compile_shader(ShaderType::FRAGMENT);
		post_compile_check();
		link_shader();
		cleanup_shader();
}

Shader_::Shader_(const char* vs_path, const char* fs_path, const char* gs_path) {

		load_shader(vs_path);
		compile_shader(ShaderType::VERTEX);
		load_shader(fs_path);
		compile_shader(ShaderType::FRAGMENT);
		load_shader(gs_path);
		compile_shader(ShaderType::GEOMETRY);
		post_compile_check();
		link_shader();
		cleanup_shader();
}


std::string Shader_::load_shader(std::string path) {
	// read from file
	std::string shader_code;
	std::ifstream shader_stream(path.c_str(), std::ios::in);
	if (shader_stream.is_open()) {
		std::stringstream sstr;
		sstr << shader_stream.rdbuf();
		shader_code = sstr.str();
		shader_stream.close();
	}
	else {
		printf("Cannot open %s\n", path);
		getchar();
		//return 0;
		throw std::runtime_error("Cannot open: " + std::string(path));
	}
}

void Shader_::compile_shader(ShaderType type) {

	if (type == ShaderType::VERTEX) {
		vertex_id = glCreateShader(GL_VERTEX_SHADER);
	}
	else if (type == ShaderType::GEOMETRY) {
		geometry_id = glCreateShader(GL_GEOMETRY_SHADER);
	}
	else if (type == ShaderType::FRAGMENT) {
		fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
	}

	std::cout << "Compiling shader : %s\n" << shader_from_path << "\n";
	char const* source_ptr = shader_code.c_str();
	glShaderSource(program_id, 1, &source_ptr, nullptr);
	glCompileShader(program_id);
}

void Shader_::post_compile_check() {
	GLint result = GL_FALSE;
	int log_length;

	glGetShaderiv(program_id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(program_id, GL_INFO_LOG_LENGTH, &log_length);
	if (log_length > 0) {
		std::vector<char> error_message(log_length + 1);
		glGetShaderInfoLog(program_id, log_length, nullptr, &error_message[0]);
		printf("ShaderInfoLog: %s\n", &error_message[0]);
	}
	else {
		std::cout << "Shader: " << program_id << " compiled OK\n";
	}
}

void Shader_::link_shader() {

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
		std::vector<char> err_msg(info_log_length + 1);
		glGetProgramInfoLog(program_id, info_log_length, NULL, &err_msg[0]);
		printf("Shader info log: %s\n", &err_msg[0]);
	}
	else {
		std::cout << "Shader: " << program_id << " linked OK\n";
	}
}

void Shader_::cleanup_shader() {
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
