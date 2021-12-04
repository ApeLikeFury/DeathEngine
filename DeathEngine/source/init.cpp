#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "init.h"
#include "window.h"
#include "imgui/imgui-master/imgui.h"
#include "imgui/imgui-master/imgui_impl_glfw.h"
#include "imgui/imgui-master/imgui_impl_opengl3.h"


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

void InitialiseImGui(window win)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(win.window_id, true);
    ImGui_ImplOpenGL3_Init("#version 430");
}

void Terminate()
{
    glfwTerminate();
}