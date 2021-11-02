#pragma once
#include "shader.h"
#include "texture.h"
#include <string>

class overlay
{
	unsigned int vao;
	shader overlay_shader;
	texture overlay_texture;

public:
	overlay();

	void BindShader(shader shader_choice);

	void BindTexture(std::string filepath);

	void Draw();
};