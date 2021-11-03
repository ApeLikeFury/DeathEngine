#pragma once
#include <string>
#include "shader.h"
#include "vec3.h"


class createobject
{
	unsigned int vao = -1;
	shader shade;
	vec2<float> centre;
	vec3<float> color;
	float radius;

public:
	createobject(std::string object_name, vec2<float> position, float size, vec3<float> my_color);

	void Draw();
};