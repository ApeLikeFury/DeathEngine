#include <GL/glew.h>
#include <string>
#include "errors.h"
#include "stb_image/stb_image.h"
#include "texture.h"

texture::texture(std::string filepath)
{
	texture::init(filepath);
}

texture::texture()
{
}

void texture::init(std::string filepath)
{
	stbi_set_flip_vertically_on_load(1);
	texture_data = stbi_load(filepath.c_str(), &texture_width, &texture_height, &texture_BPP, 4);

	Error(glGenTextures(1, &texture_id));
	Error(glBindTexture(GL_TEXTURE_2D, texture_id));

	Error(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	Error(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	Error(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	Error(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	Error(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture_width, texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data));
	Error(glBindTexture(GL_TEXTURE_2D, 0));
}

void texture::Bind(unsigned int slot)
{
	Error(glActiveTexture(GL_TEXTURE0 + slot));
	Error(glBindTexture(GL_TEXTURE_2D, texture_id));
}
