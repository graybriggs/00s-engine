
#include "texture.h"
#include "texture_loader.h"
#include "stb_image.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string_view>

Texture TextureManager::load_texture(const std::string& name, const std::string& path) {

	int width;
	int height;
	int nbr_channels;
	unsigned char* data = stbi_load(path.data(), &width, &height, &nbr_channels, 0);

    GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		std::cout << "Generated texture: `" << name << "` id: " << texture << "\n";
		//textures[name] = Texture(texture);
	}
	else {
		std::cout << "Error generating texture" << std::endl;
        return 0;
	}
	stbi_image_free(data);

    return texture;
}

Texture TextureManager::get_texture(const std::string& name) const {

	auto it = textures.find(name.data());
	if (it != std::end(textures)) {
		return it->second;
	}
	else {
		return 0;
	}
	//return 0;
}