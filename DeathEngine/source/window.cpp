#include <GLFW/glfw3.h>
#include "window.h"

window::window(const unsigned int width, const unsigned int height)
	:window_width(width), window_height(height)
{
	window_id = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
	glfwMakeContextCurrent(window_id);
}

bool window::open()
{
	update();
	clear();
	return !glfwWindowShouldClose(window_id);
}

void window::update()
{
	glfwSwapBuffers(window_id);
	glfwPollEvents();
}

void window::clear()
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);
}

void window::terminate()
{
	glfwTerminate();
}
