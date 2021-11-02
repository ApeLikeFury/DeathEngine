#pragma once
#include <vector>

class vertexbuffer
{
public:
	unsigned int buffer_id;

	vertexbuffer(std::vector<float> vertices, unsigned int elements_per_vertex, unsigned int location);

	~vertexbuffer();
};


