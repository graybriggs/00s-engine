#pragma once

#include "shader.h"

#include <GL/glew.h>
#include <GL/gl.h>

#include <glm/glm.hpp>

#include <string>
#include <unordered_map>


enum class MaterialType : std::uint8_t {
    Color,
    Diffuse,
    Textured
};

// required for swich-case on enum class
struct MaterialTypeHash {
    std::uint8_t operator()(MaterialType type) const noexcept {
        return static_cast<std::uint8_t>(type);
    }
};

class Material {
public:

    Shader* get_shader_from_material(MaterialType type);

    void add_shader(std::string name, Shader* shader);
    Shader* get_shader(std::string name);

private:
    Shader* shader;

    std::unordered_map<std::string, Shader*> shaders;
    std::unordered_map<std::string, glm::vec3> vectors;
};