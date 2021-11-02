#pragma once
#include <GLFW/glfw3.h>

class window
{
public:
	GLFWwindow* window_id;
	unsigned int window_width;
	unsigned int window_height;

	window(unsigned int width, unsigned int height);

	bool open();

	void update();

	void clear();

	void terminate();
};