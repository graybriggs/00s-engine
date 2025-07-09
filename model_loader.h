#pragma once


#include "mesh_data.h"
#include <string>
#include <vector>

struct MeshData;

std::vector<std::string> split(std::string line, char delimeter = ' ');

bool load_obj(const char* path, MeshData& data);

