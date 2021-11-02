#include "defaultobject.h"
#include <string>
#include <iostream>
#include "shader.h"
#include "vec3.h"
#include "vertexbuffer.h"

createobject::createobject(std::string object_name, vec2<float> position, float size)
{
	std::vector<float> vertex_positions;

	if (object_name == "circle")
	{
		shader circle("shaders/ Circle.vert", "shaders/Circle.frag");
		shade = circle;
		shade.Uniform1f("radius", size);
		shade.Uniform2f("centre", position.x, position.y);
		vertex_positions = { -1.0, 1.0, -1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0, -1.0, -1.0 };
	}
	else
	{
		std::cout << "invalid shape name!";
		return;
	}
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	vertexbuffer shape(vertex_positions, 2, 0);
	glBindVertexArray(0);
}

void createobject::Draw()
{
	glDepthFunc(GL_ALWAYS);
	glBindVertexArray(vao);
	shade.use();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
