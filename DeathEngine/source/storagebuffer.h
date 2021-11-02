#pragma once
#include <vector>

class storagebuffer
{
public:
	unsigned int buffer_id;

	storagebuffer(std::vector<float> data, unsigned int location);
};