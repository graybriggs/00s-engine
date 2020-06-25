#pragma once

#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct MeshData {

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	std::vector<unsigned int> vertex_indices;
	std::vector<unsigned int> uv_indices;
	std::vector<unsigned int> normal_indices;

};

std::vector<std::string> split(std::string line, char sep = ' ') {

	std::vector<std::string> tokens;
	std::istringstream iss(line);
	std::string token;
	while (std::getline(iss, token, sep)) {
		tokens.push_back(token);
	}
	return tokens;
}


bool load_obj(const char* path, MeshData& data) {

	std::vector<glm::vec3> vertices; // (x,y,z[,w])
	std::vector<glm::vec2> texture_coordinates; // (u, v [,w])
	std::vector<glm::vec3> vertex_normals; // (x,y,z)
	std::vector<unsigned int> vertex_indices;
	std::vector<unsigned int> texture_uv_indices;
	std::vector<unsigned int> normal_indices;


	std::ifstream ifs;
	ifs.open(path);

	if (!ifs.is_open()) {
		return false;
	}

	std::string line;
	while (std::getline(ifs, line)) {

		if (line[0] == 'v' && line[1] == ' ') {
			std::vector<std::string> tokens = split(line);
			glm::vec3 vertex;
			vertex.x = std::stof(tokens[1]);
			vertex.y = std::stof(tokens[2]);
			vertex.z = std::stof(tokens[3]);
			vertices.push_back(vertex);
		}
		else if (line[0] == 'v' && line[1] == 't') {
			std::vector<std::string> tokens = split(line);
			glm::vec2 vt;
			vt.x = std::stof(tokens[1]);
			vt.y = std::stof(tokens[2]);
			//vt.z = std::stof(tokens[3]);
			texture_coordinates.push_back(vt);
		}
		else if (line[0] == 'v' && line[1] == 'n') {
			std::vector<std::string> tokens = split(line);
			glm::vec3 normal;
			normal.x = std::stof(tokens[1]);
			normal.y = std::stof(tokens[2]);
			normal.z = std::stof(tokens[3]);
			vertex_normals.push_back(normal);
		}
		// if there are no normals in the exported file then this will crash - fix
		if (line[0] == 'f') { // f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3 ...
			std::vector<std::string> tokens = split(line);
			std::vector<std::string> tri_data1 = split(tokens[1], '/');
			std::vector<std::string> tri_data2 = split(tokens[2], '/');
			std::vector<std::string> tri_data3 = split(tokens[3], '/');
			vertex_indices.push_back(std::stoi(tri_data1[0]));
			vertex_indices.push_back(std::stoi(tri_data2[0]));
			vertex_indices.push_back(std::stoi(tri_data3[0]));
			if (tri_data1[1].size() > 0) {
				texture_uv_indices.push_back(std::stoi(tri_data1[1]));
				texture_uv_indices.push_back(std::stoi(tri_data2[1]));
				texture_uv_indices.push_back(std::stoi(tri_data3[1]));
			}
			normal_indices.push_back(std::stoi(tri_data1[2]));
			normal_indices.push_back(std::stoi(tri_data2[2]));
			normal_indices.push_back(std::stoi(tri_data3[2]));
		}
	}


	// vertices
	for (std::size_t i = 0; i < vertex_indices.size(); ++i) {
		unsigned int vertex_index = vertex_indices[i];
		glm::vec3 vert = vertices[vertex_index - 1];
		data.vertices.push_back(vert);
	}

	// texture uvs
	for (std::size_t i = 0; i < texture_uv_indices.size(); ++i) {
		unsigned int uv_index = texture_uv_indices[i];
		glm::vec2 uv = texture_coordinates[uv_index - 1];
		data.uvs.push_back(uv);
	}

	// normals
	for (std::size_t i = 0; i < normal_indices.size(); ++i) {
		unsigned int normal_index = normal_indices[i];
		glm::vec3 vert = vertex_normals[normal_index - 1];
		data.normals.push_back(vert);
	}

	data.vertex_indices = vertex_indices;

	for (std::size_t i = 0; i < vertex_indices.size(); ++i) {
		unsigned int ind = vertex_indices[i];
		data.vertex_indices.push_back(ind - 1);
	}

	data.uv_indices = texture_uv_indices;
	data.normal_indices = normal_indices;

	return true;
}





#endif
