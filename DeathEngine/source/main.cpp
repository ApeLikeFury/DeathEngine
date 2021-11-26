#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "window.h"
#include "shader.h"
#include "init.h"
#include "model.h"
#include "inputs.h"
#include "vertexbuffer.h"
#include "texture.h"
#include "overlay.h"
#include "vec3.h"
#include "storagebuffer.h"

extern vec3<float> CameraRotation;
extern vec3<float> CameraPosition;
extern vec3<float> PlayerPosition;
extern vec3<float> PlayerRotation;
extern float speed;

int main(void)
{
    InitialiseGLFW(4.3);
    window win(1000, 1000);
    InitialiseGLEW();
    glfwSwapInterval(1);
    //InitialiseInputs(win.window_id);

    shader dot("shaders/3Dproject.vert", "shaders/DotProduct.frag");

    shader white("shaders/fullraytracing.vert", "shaders/fullraytracing.frag");
    white.Uniform1i("iTexture", 0);

    std::vector<float> positions =
    {
        1.0,1.0, 1.0,-1.0, -1.0,1.0,
        -1.0,-1.0, 1.0,-1.0, -1.0,1.0
    };

    vertexarray vao;
    vao.bind();
    vertexbuffer canvas(positions, 2, 0);
    vao.unbind();

    model landscape;
    landscape.ImportObj("models/monkeyscene.obj");
    landscape.BindShader(dot);
    landscape.ImportTexture("textures/ruby.png");
    landscape.LoadModel();

    landscape.rotation.y == 90;

    std::vector<float> random;

    storagebuffer vertexpositions(landscape.vertex_positions, 0);
    storagebuffer vertexnormals(landscape.vertex_normals, 1);

    speed = 100;

    float LastTime = glfwGetTime();

    while (win.open())
    {
        PlayerControls(win.window_id, LastTime);

        dot.Uniform3f("iCameraPosition", CameraPosition.x, CameraPosition.y, CameraPosition.z);
        dot.Uniform3f("iLightPosition", 0, 2500, 0);
        dot.Uniform1f("iTime", glfwGetTime());
        dot.Uniform3f("iCameraRotation", CameraRotation.x, CameraRotation.y, CameraRotation.z);


        landscape.Draw();
    }

    win.terminate();
}