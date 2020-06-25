#pragma once
#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <glew.h>
#include <gl/GL.h>


GLuint load_shaders(const char * vertex_file_path, const char * fragment_file_path);

#endif
