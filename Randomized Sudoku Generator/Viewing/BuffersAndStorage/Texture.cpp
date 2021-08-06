#include "Texture.h"
#include <stb_image.h>
#include <GL/glew.h>

Texture::Texture(const std::string& filepath) {
	stbi_set_flip_vertically_on_load(1);
	buffer = stbi_load(filepath.c_str(), &width, &height, &mBPP, 4);

	glGenTextures(1, &renderId);
	glBindTexture(GL_TEXTURE_2D, renderId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

	glBindTexture(GL_TEXTURE_2D, 0);
	if (buffer) {
		stbi_image_free(buffer);
	}
}

void Texture::Bind(unsigned int slot) {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, renderId);
}

Texture::~Texture() {
	glDeleteBuffers(1, &renderId);
}