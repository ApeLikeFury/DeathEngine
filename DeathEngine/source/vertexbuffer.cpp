#include <GL/glew.h>
#include <vector>
#include "errors.h"
#include "vertexbuffer.h"

vertexbuffer::vertexbuffer(std::vector<float> vertices, unsigned int elements_per_vertex, unsigned int location)
{
	Error(glGenBuffers(1, &buffer_id));
	Error(glBindBuffer(GL_ARRAY_BUFFER, buffer_id));
	Error(glBufferData(GL_ARRAY_BUFFER, size(vertices)*sizeof(float), vertices.data(), GL_STATIC_DRAW));
	Error(glEnableVertexAttribArray(location));
	Error(glVertexAttribPointer(location, elements_per_vertex, GL_FLOAT, GL_FALSE, sizeof(float) * elements_per_vertex, 0));
	Error(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

vertexbuffer::~vertexbuffer()
{
	Error(glDeleteBuffers(1, &buffer_id));
}
