#include "framebuffer.h"
#include "texture.h"
#include "errors.h"
#include "window.h"


/*framebuffer::framebuffer(window mywindow)
{
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

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
}

void framebuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void framebuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}*/
