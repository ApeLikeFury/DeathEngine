#include <GL/glew.h>
#include "overlay.h"
#include "vertexbuffer.h"
#include <vector>

overlay::overlay()
{
	std::vector<float> positions = 
	{
		1.0,  1.0, 
		1.0, -1.0, 
	   -1.0,  1.0,

	   -1.0, -1.0, 
		1.0, -1.0, 
	   -1.0,  1.0,
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	vertexbuffer overlay(positions, 2, 0);

	glBindVertexArray(0);
}

void overlay::BindShader(shader shader_choice)
{
	overlay_shader = shader_choice;
}

void overlay::BindTexture(std::string filepath)
{
	overlay_texture.init(filepath);
}

void overlay::Draw()
{
	glBindVertexArray(vao);
	overlay_shader.use();
	overlay_texture.Bind(0);
	glDrawArrays(GL_TRIANGLES, 0, 12);
	glBindVertexArray(0);
}
