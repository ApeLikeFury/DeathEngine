#pragma once

#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
using namespace std;

#define ASSERT(x) if(!(x)) __debugbreak();
#define Error(x) ClearError(); x; ASSERT(CheckError(#x, __FILE__, __LINE__));


static void ClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool CheckError(string function, string file, int line)
{
	while (GLenum error = glGetError())
	{
		cout << "OpenGL Error (" << error << ") Line (" << line << ") File (" << file << ")" << endl;
		return false;
	}
	return true;
}
