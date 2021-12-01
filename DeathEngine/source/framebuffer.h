#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "texture.h"
#include "window.h"
#include "vertexarray.h"
#include "shader.h"

class framebuffer
{
	unsigned int fbo;
	unsigned int fbt;
	unsigned int rbo;

	vertexarray vao;

	shader framebufferprogram;

public:
	framebuffer(window mywindow);

	void bind();

	void unbind();

	void clearbufferbit();

	void Draw();

};