#include <GL/glew.h>
#include <GLFW/glfw3.h>
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
#include "defaultobject.h"

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

    shader white("shaders/3DProject.vert", "shaders/DotProduct.frag");
    white.Uniform1i("iTexture", 0);

    model landscape;
    landscape.ImportObj("models/monkeyblocks.obj");
    landscape.ImportTexture("textures/green.jpg");
    landscape.BindShader(white);
    landscape.LoadModel();
    landscape.rotation.y = 180;

    shader raytrace("shaders/Simple2D.vert", "shaders/Raytrace.frag");
    
    storagebuffer vertices(landscape.vertex_positions, 0);

    createobject circle("circle", { 0, 0 }, 1.0);

    
    speed = 100;

    float LastTime = glfwGetTime();

    while (win.open())
    {
        PlayerControls(win.window_id, LastTime);

        white.Uniform3f("iCameraPosition", CameraPosition.x, CameraPosition.y, CameraPosition.z);
        white.Uniform3f("iCameraRotation", CameraRotation.x, CameraRotation.y, CameraRotation.z);
        white.Uniform3f("iPlayerPosition", PlayerPosition.x, PlayerPosition.y, PlayerPosition.z);

        white.Uniform2f("iScreenResolution", win.window_width, win.window_height);
        white.Uniform3f("iLightPosition", 0, -100, 0);
        white.Uniform1f("iTime", glfwGetTime());

        raytrace.Uniform3f("iCameraPosition", CameraPosition.x, CameraPosition.y, CameraPosition.z);

        landscape.Draw();
        circle.Draw();
    }

    win.terminate();
}