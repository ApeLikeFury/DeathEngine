#pragma once
#include <string>
#include "shader.h"
#include "vec3.h"


class createobject
{
	unsigned int vao = -1;
	shader shade;
public:
	createobject(std::string object_name, vec2<float> position, float size);

	void Draw();
};