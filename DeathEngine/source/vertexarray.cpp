#include "vertexarray.h"
#include <GL/glew.h>

vertexarray::vertexarray()
{
	glGenVertexArrays(1, &vao);
}

void vertexarray::bind()
{
	glBindVertexArray(vao);
}

void vertexarray::unbind()
{
	glBindVertexArray(0);
}
