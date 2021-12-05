#pragma once
#include <vector>
#include "vec3.h"
#include "shader.h"
#include "texture.h"
#include "vertexarray.h"
#include <string>

class model
{
public:

	std::string object_name;
	std::vector<float> vertex_positions;
	std::vector<float> vertex_texcoords;
	std::vector<float> vertex_normals;


	shader object_shader;
	texture model_texture;
	texture model_specmap;
	vertexarray vao;

	vec3<float> rotation = { 0.0, 0.0, 0.0 };
	vec3<float> location = { 0.0, 0.0, 0.0 };
	vec3<float> centre = { 0.0, 0.0, 0.0 };

	void GetCentre();

	model();

	void SmoothNormals();
	
	void BindShader(shader shader_choice);

	void SetUniforms();

	void BindTexture(texture texture_choice);

	void BindSpecmap(texture specmap_choice);

	void Load();

	void Draw();
};