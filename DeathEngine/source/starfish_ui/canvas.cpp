#include "canvas.h"
#include "../vertexbuffer.h"
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../shader.h"
#include "../texture.h"

rectangle::rectangle(float x1, float y1, float x2, float y2)
	:x1(x1), y1(y1), x2(x2), y2(y2)
{
	basic2D.init("starfish_shaders/rectangle.vert", "starfish_shaders/rectangle.frag");
	basic2D.Uniform1i("iTexture", 0);

	std::vector<float> positions = { 1.0, -1.0, -1.0, -1.0, -1.0, 1.0, 1.0, 1.0, 1.0, -1.0, -1.0,  1.0 };
	std::vector<float> texcoords = { 1.0,  0.0,  0.0,  0.0,  0.0, 1.0, 1.0, 1.0, 1.0,  0.0,  0.0,  1.0 };

	vao.bind();

	vertexbuffer vertexpositions(positions, 2, 0);
	vertexbuffer vertextexcoords(texcoords, 2, 1);

	vao.unbind();
}

void rectangle::Draw()
{
	basic2D.use();
	basic2D.Uniform2f("iPos1", x1, y1);
	basic2D.Uniform2f("iPos1", x2, y2);

	basic2D.Uniform1i("iTexture", 0);

	vao.bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	vao.unbind();
}
