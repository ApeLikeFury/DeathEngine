#pragma once

#include "../vertexarray.h"
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../shader.h"

class rectangle
{
	shader basic2D;
	vertexarray vao;

	float x1, y1, x2, y2;

public:
	rectangle(float x1, float y1, float x2, float y2);

	void Draw();
};