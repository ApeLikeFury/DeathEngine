#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "init.h"

void InitialiseGLFW(int OpenGL_Version)
{
    if (!glfwInit())
        std::cout << "error! GLFW Init" << std::endl;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OpenGL_Version);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OpenGL_Version);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSwapInterval(1);
}

void InitialiseGLEW()
{
    glewInit();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glClearColor(0.7, 0.7, 1, 1);
}

void Terminate()
{
    glfwTerminate();
}