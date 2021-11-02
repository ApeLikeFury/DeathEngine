#pragma once
#include <vector>
#include <string>
#include "vertexbuffer.h"
#include "shader.h"
#include "vec3.h"
#include "texture.h"

class model
{
	void SetUniforms();

	void SetCentre();

public:
	std::vector<float> vertex_positions;
	std::vector<float> vertex_texcoords;
	std::vector<float> vertex_normals;

	shader object_shader;
	texture model_texture;
	unsigned int vao;

	vec3<float> rotation = { 0.0, 0.0, 0.0 };
	vec3<float> location = { 0.0, 0.0, 0.0 };
	vec3<float> centre   = { 0.0, 0.0, 0.0 };

	void ImportObj(std::string filepath);

	void ImportTexture(std::string filepath);

	void BindShader(shader shader_choice);

	void Draw();

	void LoadModel();

	unsigned int length();

	void Rotate(vec3<float> xyz);
	
	void MoveBy(vec3<float> xyz);
};