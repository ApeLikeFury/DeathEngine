#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "errors.h"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "vec3.h"
#include "model.h"
#include "vertexbuffer.h"
#include "shader.h"
#include "texture.h"

// private members

void model::SetUniforms()
{
	object_shader.Uniform3f("iObjectRotation", rotation.x, rotation.y, rotation.z);
	object_shader.Uniform3f("iObjectLocation", location.x, location.y, location.z);
	object_shader.Uniform3f("iObjectCentre", centre.x, centre.y, centre.z);
}

void model::SetCentre()
{
	vec3<float> highest = { vertex_positions[0], vertex_positions[1], vertex_positions[2] };
	vec3<float> lowest  = { vertex_positions[0], vertex_positions[1], vertex_positions[2] };

	for (unsigned int i = 0; i < size(vertex_positions)/3; i++)
	{
		unsigned int index = i * 3;
		vec3<float> xyz = { vertex_positions[index], vertex_positions[index + 1], vertex_positions[index + 2] };

		if (xyz.x > highest.x)
		{
			highest.x = xyz.x;
		}
		else if (xyz.x < lowest.x)
		{
			lowest.x = xyz.x;
		}

		if (xyz.y > highest.y)
		{
			highest.y = xyz.y;
		}
		else if (xyz.y < lowest.y)
		{
			lowest.y = xyz.y;
		}

		if (xyz.z > highest.z)
		{
			highest.z = xyz.z;
		}
		else if (xyz.z < lowest.z)
		{
			lowest.z = xyz.z;
		}
	}

	float avgx = (highest.x + lowest.x) / 2.0;
	float avgy = (highest.y + lowest.y) / 2.0;
	float avgz = (highest.z + lowest.z) / 2.0;

	centre = { avgx, avgy, avgz };
}

// public members


void model::ImportObj(std::string filepath)
{
	std::stringstream ss;
	std::fstream myFile;

	std::vector<vec3<float>> temp_vertex_normals;
	std::vector<vec2<float>> temp_vertex_texcoords;
	std::vector<vec3<float>> temp_vertex_positions;

	std::vector<unsigned int> indices;
	std::vector<unsigned int> vt_indices;
	std::vector<unsigned int> vn_indices;

	myFile.open(filepath, std::ios::in);
	if (myFile.is_open())
	{
		std::string line;
		std::string prefix;
		while (getline(myFile, line))
		{
			ss.clear();
			ss.str(line);
			ss >> prefix;

			if (prefix == "vn")
			{
				vec3<float> n;
				ss >> n.x >> n.y >> n.z;
				temp_vertex_normals.push_back(n);
			}
			else if (prefix == "vt")
			{
				vec2<float> n;
				ss >> n.x >> n.y;
				temp_vertex_texcoords.push_back(n);
			}
			else if (prefix == "v")
			{
				vec3<float> n;
				ss >> n.x >> n.y >> n.z;
				temp_vertex_positions.push_back(n);
			}
			else if (prefix == "f")
			{
				unsigned int counter = 0;
				unsigned int x;
				while (ss >> x)
				{
					switch (counter)
					{
					case 0:
						x -= 1;
						indices.push_back(x);
						break;
					case 1:
						x -= 1;
						vt_indices.push_back(x);
						break;
					case 2:
						x -= 1;
						vn_indices.push_back(x);
						break;
					}

					char next = ss.peek();
					if (next == '/' || next == ' ')
					{
						counter++;
						ss.ignore(1, next);
					}

					if (counter > 2)
					{
						counter = 0;
					}
				}
			}
		}

		for (unsigned int i = 0; i < size(indices); i++)
		{
			unsigned int index = indices[i];
			unsigned int vt_index = vt_indices[i];
			unsigned int vn_index = vn_indices[i];

			vec3<float> position = temp_vertex_positions[index];
			vec2<float> texcoord = temp_vertex_texcoords[vt_index];
			vec3<float> normal = temp_vertex_normals[vn_index];

			vertex_positions.push_back(position.x);
			vertex_positions.push_back(position.y);
			vertex_positions.push_back(position.z);

			vertex_texcoords.push_back(texcoord.x);
			vertex_texcoords.push_back(texcoord.y);

			vertex_normals.push_back(normal.x);
			vertex_normals.push_back(normal.y);
			vertex_normals.push_back(normal.z);
		}
	}
	else
	{
		std::cout << "failed to open file!";
	}
}

void model::ImportTexture(std::string filepath)
{
	model_texture.init(filepath);
}

void model::BindShader(shader shader_choice)
{
	object_shader = shader_choice;
}

void model::Draw()
{
	glDepthFunc(GL_LESS);
	object_shader.use();
	model_texture.Bind(0);
	SetUniforms();
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, size(vertex_positions));
}

void model::LoadModel()
{
	SetCentre();
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	vertexbuffer positions(vertex_positions, 3, 0);
	vertexbuffer normals(vertex_normals, 3, 1);
	vertexbuffer texcoords(vertex_texcoords, 2, 2);

	glBindVertexArray(0);
}

unsigned int model::length()
{
	return size(vertex_positions);
}

void model::Rotate(vec3<float> xyz)
{
	rotation.x += xyz.x;
	rotation.y += xyz.y;
	rotation.z += xyz.z;
}

void model::MoveBy(vec3<float> xyz)
{
	location.x += xyz.x;
	location.y += xyz.y;
	location.z += xyz.z;
}
