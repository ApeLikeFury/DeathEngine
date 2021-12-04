#pragma once
#include <vector>
#include <string>
#include "vertexbuffer.h"
#include "shader.h"
#include "vec3.h"
#include "texture.h"
#include "vertexarray.h"
#include "model.h"

class entity
{
	void SetUniforms();

public:
	std::vector<float> vertex_positions;
	std::vector<float> vertex_texcoords;
	std::vector<float> vertex_normals;

	std::vector<model> models;

	shader object_shader;
	texture model_texture;
	vertexarray vao;

	vec3<float> rotation = { 0.0, 0.0, 0.0 };
	vec3<float> location = { 0.0, 0.0, 0.0 };
	vec3<float> centre   = { 0.0, 0.0, 0.0 };

	void ImportObj(std::string filepath);

	void Draw();

	void LoadModels();

	void BindAllShaders(shader shader_choice);

	void BindAllTextures(std::string filepath);

	void Rotate(vec3<float> xyz);
	
	void MoveBy(vec3<float> xyz);
};