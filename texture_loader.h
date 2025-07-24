#pragma once

#include "texture.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include <string>
#include <unordered_map>

class TextureManager {
public:
    TextureManager() = default;

    Texture load_texture(const std::string& name, const std::string& path);
    Texture get_texture(const std::string& name) const;
private:
    //std::unordered_map<std::string, GLuint> textures;
    std::unordered_map<std::string, Texture> textures;
};