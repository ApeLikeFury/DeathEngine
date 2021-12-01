#include "framebuffer.h"
#include "texture.h"
#include "errors.h"
#include "window.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "vertexbuffer.h"
#include "shader.h"


framebuffer::framebuffer(window mywindow)
{
	Error(glGenFramebuffers(1, &fbo));
	Error(glBindFramebuffer(GL_FRAMEBUFFER, fbo));

	Error(glGenTextures(1, &fbt));
	Error(glBindTexture(GL_TEXTURE_2D, fbt));
	Error(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mywindow.window_width, mywindow.window_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
	Error(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	Error(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	Error(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	Error(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	Error(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbt, 0));

	Error(glGenRenderbuffers(1, &rbo));
	Error(glBindRenderbuffer(GL_RENDERBUFFER, rbo));
	Error(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, mywindow.window_width, mywindow.window_height));
	Error(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo));

	auto fbostatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (fbostatus != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Framebuffer error: " << fbostatus << std::endl;
	}

	shader fbs("shaders/framebuffer.vert", "shaders/framebuffer.frag");
	framebufferprogram = fbs;
	framebufferprogram.Uniform1i("iTexture", 0);

	std::vector<float> positions = { 1.0, -1.0, -1.0, -1.0, -1.0, 1.0, 1.0, 1.0, 1.0, -1.0, -1.0,  1.0 };
	std::vector<float> texcoords = { 1.0,  0.0,  0.0,  0.0,  0.0, 1.0, 1.0, 1.0, 1.0,  0.0,  0.0,  1.0 };

	vao.bind();
	vertexbuffer vpositions(positions, 2, 0);
	vertexbuffer vtexcoords(texcoords, 2, 1);
	vao.unbind();
}

void framebuffer::bind()
{
	Error(glBindFramebuffer(GL_FRAMEBUFFER, fbo));
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
}

void framebuffer::unbind()
{
	Error(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void framebuffer::Draw()
{
	glDisable(GL_DEPTH_TEST);
	framebufferprogram.use();
	glBindTexture(GL_TEXTURE_2D, fbt);

	vao.bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	vao.unbind();

	glEnable(GL_DEPTH_TEST);
}

void framebuffer::clearbufferbit()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


