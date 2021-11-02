#pragma once
#include <string>

class texture
{
	unsigned int texture_id;
	unsigned char* texture_data;
	int texture_width, texture_height, texture_BPP;

public:
	texture(std::string filepath);

	texture();

	void init(std::string filepath);

	void Bind(unsigned int slot);
};