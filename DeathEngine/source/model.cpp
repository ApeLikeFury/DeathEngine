#include "model.h"
#include <vector>
#include "shader.h"
#include "texture.h"
#include "vertexbuffer.h"
#include "vertexarray.h"
#include "vec3.h"
#include <iostream>

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

model::model()
{
	
}

void model::SmoothNormals()
{
	std::vector<float> newnormals;

	if (size(vertex_positions) != size(vertex_normals))
	{
		std::cout << "error! vertex positions and normals different length... object: " << object_name;
		return;
	}

	for (size_t i = 0; i < size(vertex_positions); i+=3)
	{
		int index = i * 3;
		vec3<float> nnorm;
		vec3<float> ipos = { vertex_positions[i], vertex_positions[i + 1], vertex_positions[i + 2] };
		vec3<float> inorm = { vertex_normals[i], vertex_normals[i + 1], vertex_normals[i + 2] };

		for (size_t j = 0; j < size(vertex_positions); j+=3)
		{
			if (j == i)
			{
				continue;
			}

			vec3<float> jpos = { vertex_positions[j], vertex_positions[j + 1], vertex_positions[j + 2] };
			vec3<float> jnorm = { vertex_normals[j], vertex_normals[j + 1], vertex_normals[j + 2] };

			if (jpos.x == ipos.x && jpos.y == ipos.y && jpos.z == ipos.z)
			{
				//continue here
			}

		}
	}
}



void model::BindShader(shader shader_choice)
{
	object_shader = shader_choice;
}

void model::SetUniforms()
{
	object_shader.Uniform3f("iObjectRotation", rotation.x, rotation.y, rotation.z);
	object_shader.Uniform3f("iObjectLocation", location.x, location.y, location.z);
	object_shader.Uniform3f("iObjectCentre", centre.x, centre.y, centre.z);
}

void model::BindTexture(texture texture_choice)
{
	model_texture = texture_choice;
}

void model::Load()
{
	GetCentre();

	vao.bind();

	vertexbuffer positions(vertex_positions, 3, 0);
	vertexbuffer normals(vertex_normals, 3, 1);
	vertexbuffer texcoords(vertex_texcoords, 2, 2);

	vao.unbind();
}

void model::Draw()
{
	object_shader.use();
	model_texture.Bind(0);

	SetUniforms();

	vao.bind();

	glDrawArrays(GL_TRIANGLES, 0, size(vertex_positions));

	vao.unbind();
}

