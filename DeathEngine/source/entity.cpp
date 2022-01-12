#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "errors.h"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "vec3.h"
#include "entity.h"
#include "vertexbuffer.h"
#include "shader.h"
#include "texture.h"
#include "model.h"

// private members

void entity::SetUniforms()
{
	object_shader.Uniform3f("iObjectRotation", rotation.x, rotation.y, rotation.z);
	object_shader.Uniform3f("iObjectLocation", location.x, location.y, location.z);
	object_shader.Uniform3f("iObjectCentre", centre.x, centre.y, centre.z);
}


// public members

void entity::ImportObj(std::string filepath)
{
	std::stringstream ss;
	std::fstream myFile;

	model currentmodel;

	std::vector<vec3<float>> temp_vertex_normals;
	std::vector<vec2<float>> temp_vertex_texcoords;
	std::vector<vec3<float>> temp_vertex_positions;

	std::vector<unsigned int> indices;
	std::vector<unsigned int> vt_indices;
	std::vector<unsigned int> vn_indices;



	myFile.open(filepath, std::ios::in);
	if (myFile.is_open())
	{
		int objects = 0;

		std::string line;
		std::string prefix;
		while (getline(myFile, line))
		{
			ss.clear();
			ss.str(line);
			ss >> prefix;

			if (prefix == "o")
			{
				objects++;

				if (size(indices) > 0)
				{
					for (unsigned int i = 0; i < size(indices); i++)
					{
						unsigned int index = indices[i];
						unsigned int vt_index = vt_indices[i];
						unsigned int vn_index = vn_indices[i];

						if (size(temp_vertex_positions) < index)
						{
							std::cout << "error: positions array too short in model: " << currentmodel.object_name;
							__debugbreak;
						}
						else if (size(temp_vertex_texcoords) < vt_index)
						{
							std::cout << "error: positions array too short in model: " << currentmodel.object_name;
							__debugbreak;
						}
						else if (size(temp_vertex_normals) < vn_index)
						{
							std::cout << "error: positions array too short in model: " << currentmodel.object_name;
							__debugbreak;
						}

						vec3<float> position = temp_vertex_positions[index];
						vec2<float> texcoord = temp_vertex_texcoords[vt_index];
						vec3<float> normal = temp_vertex_normals[vn_index];

						currentmodel.vertex_positions.push_back(position.x);
						currentmodel.vertex_positions.push_back(position.y);
						currentmodel.vertex_positions.push_back(position.z);

						currentmodel.vertex_texcoords.push_back(texcoord.x);
						currentmodel.vertex_texcoords.push_back(texcoord.y);

						currentmodel.vertex_normals.push_back(normal.x);
						currentmodel.vertex_normals.push_back(normal.y);
						currentmodel.vertex_normals.push_back(normal.z);

						vertex_positions.push_back(position.x);
						vertex_positions.push_back(position.y);
						vertex_positions.push_back(position.z);

						vertex_texcoords.push_back(texcoord.x);
						vertex_texcoords.push_back(texcoord.y);

						vertex_normals.push_back(normal.x);
						vertex_normals.push_back(normal.y);
						vertex_normals.push_back(normal.z);
					}

					models.push_back(currentmodel);
				}

				model newmodel;
				currentmodel = newmodel;
				ss >> currentmodel.object_name;

				indices.clear();
				vt_indices.clear();
				vn_indices.clear();
			}
			else if (prefix == "vn")
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
				n.x *= 100;
				n.y *= 100;
				n.z *= 100;
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

		objects++;

		if (size(indices) > 0)
		{
			for (unsigned int i = 0; i < size(indices); i++)
			{
				unsigned int index = indices[i];
				unsigned int vt_index = vt_indices[i];
				unsigned int vn_index = vn_indices[i];

				if (size(temp_vertex_positions) < index)
				{
					std::cout << "error: positions array too short in model: " << currentmodel.object_name;
					__debugbreak;
				}
				else if (size(temp_vertex_texcoords) < vt_index)
				{
					std::cout << "error: positions array too short in model: " << currentmodel.object_name;
					__debugbreak;
				}
				else if (size(temp_vertex_normals) < vn_index)
				{
					std::cout << "error: positions array too short in model: " << currentmodel.object_name;
					__debugbreak;
				}

				vec3<float> position = temp_vertex_positions[index];
				vec2<float> texcoord = temp_vertex_texcoords[vt_index];
				vec3<float> normal = temp_vertex_normals[vn_index];

				currentmodel.vertex_positions.push_back(position.x);
				currentmodel.vertex_positions.push_back(position.y);
				currentmodel.vertex_positions.push_back(position.z);

				currentmodel.vertex_texcoords.push_back(texcoord.x);
				currentmodel.vertex_texcoords.push_back(texcoord.y);

				currentmodel.vertex_normals.push_back(normal.x);
				currentmodel.vertex_normals.push_back(normal.y);
				currentmodel.vertex_normals.push_back(normal.z);

				vertex_positions.push_back(position.x);
				vertex_positions.push_back(position.y);
				vertex_positions.push_back(position.z);

				vertex_texcoords.push_back(texcoord.x);
				vertex_texcoords.push_back(texcoord.y);

				vertex_normals.push_back(normal.x);
				vertex_normals.push_back(normal.y);
				vertex_normals.push_back(normal.z);
			}

			models.push_back(currentmodel);
		}
		

	}
	else
	{
		std::cout << "failed to open file! " << filepath;
	}
}


void entity::Draw()
{
	for (size_t i = 0; i < size(models); i++)
	{
		models[i].Draw();
	}
}

void entity::LoadModels()
{
	for (size_t i = 0; i < size(models); i++)
	{
		models[i].Load();
	}
}

void entity::BindAllShaders(shader shader_choice)
{
	for (size_t i = 0; i < size(models); i++)
	{
		models[i].object_shader = shader_choice;
	}
}

void entity::BindAllTextures(std::string filepath)
{
	texture tex;
	tex.init(filepath);

	for (size_t i = 0; i < size(models); i++)
	{
		models[i].model_texture = tex;
	}
}



void entity::Rotate(vec3<float> xyz)
{
	rotation.x += xyz.x;
	rotation.y += xyz.y;
	rotation.z += xyz.z;
}

void entity::MoveBy(vec3<float> xyz)
{
	location.x += xyz.x;
	location.y += xyz.y;
	location.z += xyz.z;
}
