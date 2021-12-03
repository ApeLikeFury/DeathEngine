#include "model.h"
#include <vector>
#include "shader.h"
#include "texture.h"

void model::GetCentre()
{
	int count = size(vertex_positions);

	vec3<float> sum = { 0,0,0 };

	for (size_t i = 0; i < count; i+=3)
	{
		sum.x += vertex_positions[i];
		sum.y += vertex_positions[i+1];
		sum.z += vertex_positions[i+2];
	}

	sum.x /= count;
	sum.y /= count;
	sum.z /= count;

	centre = sum;
}

model::model(std::vector<float> vertex_positions, std::vector<float> vertex_texcoords, std::vector<float> vertex_normals)
	:vertex_positions(vertex_positions), vertex_texcoords(vertex_texcoords), vertex_normals(vertex_normals)
{
	GetCentre();
}

model::model()
{
	
}

void model::BindShader(shader shader_choice)
{
	object_shader = shader_choice;
}

void model::BindTexture(texture texture_choice)
{
	model_texture = texture_choice;
}

