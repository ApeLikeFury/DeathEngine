#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "window.h"
#include "shader.h"
#include "init.h"
#include "entity.h"
#include "inputs.h"
#include "vertexbuffer.h"
#include "texture.h"
#include "overlay.h"
#include "vec3.h"
#include "storagebuffer.h"
#include "framebuffer.h"
#include "userinterface.h"
#include "texture.h"

extern vec3<float> CameraRotation;
extern vec3<float> CameraPosition;
extern vec3<float> PlayerPosition;
extern vec3<float> PlayerRotation;

int main(void)
{
    InitialiseGLFW(4.3);
    window win(1920, 1080);
    InitialiseGLEW();
    glfwSwapInterval(1);
    InitialiseInputs(win);
    InitialiseImGui(win);


    shader standard("shaders/Standard.vert", "shaders/Standard.frag");
    standard.Uniform1i("iTexture", 0);

    shader reflections("shaders/RaytracedReflections.vert", "shaders/RaytracedReflections.frag");

    texture wallpaper("textures/wallpaper.jpg");
    texture flooring("textures/Wood 02 Color 02.png");

    entity room;
    room.ImportObj("models/interior.obj");
    room.BindAllShaders(standard);
    room.BindAllTextures("textures/Wood 02 Color 01.png");

    room.models[2].BindTexture(wallpaper);
    room.models[0].BindTexture(flooring);

    room.models[3].BindShader(reflections);
    room.models[3].BindTexture(wallpaper);

    room.LoadModels();

    entity test;
    test.ImportObj("models/environment.obj");
    test.location.x = 1000;

    storagebuffer vertexpositions(room.vertex_positions, 0);
    storagebuffer vertexnormals(room.vertex_normals, 1);
    storagebuffer vertextexcoords(room.vertex_texcoords, 2);


    std::vector<float> lightpositions = { 0, 0.5, 0 };

    storagebuffer lightsources(lightpositions, 3);

    framebuffer fbo(win);

    float LastTime = glfwGetTime();

    while (win.open())
    {
        if (PlayerControls(win, LastTime)) { break; }
       
        standard.use();
        standard.Uniform3f("iCameraPosition", CameraPosition.x, CameraPosition.y, CameraPosition.z);
        standard.Uniform1f("iTime", glfwGetTime());
        standard.Uniform3f("iCameraRotation", CameraRotation.x, CameraRotation.y, CameraRotation.z);
        standard.Uniform2f("iScreenResolution", win.window_width, win.window_height);

        reflections.use();
        reflections.Uniform3f("iCameraPosition", CameraPosition.x, CameraPosition.y, CameraPosition.z);
        reflections.Uniform1f("iTime", glfwGetTime());
        reflections.Uniform3f("iCameraRotation", CameraRotation.x, CameraRotation.y, CameraRotation.z);
        reflections.Uniform2f("iScreenResolution", win.window_width, win.window_height);

        fbo.bind();

        room.Draw();
        //mirrors.Draw();

        fbo.unbind();

        fbo.Draw();

        //RenderUI();
    }

    win.terminate();
}