#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include <string>
#include <unordered_map>


class TextureManager {
public:
    TextureManager() = default;

    GLuint load_texture(std::string name, std::string path);
    GLuint get_texture(std::string name);
private:
    std::unordered_map<std::string, GLuint> textures;
};