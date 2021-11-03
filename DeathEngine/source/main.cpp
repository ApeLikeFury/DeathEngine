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

    createobject circle1("circle", { 0.0,0.2 }, 0.3, { 1.0, 1.0, 0.0 });
    createobject circle2("square", { -0.3,-0.2 }, 0.2, { 1.0, 0.0, 1.0 });


    while (win.open())
    {
        circle2.Draw();
        circle1.Draw();
    }

    win.terminate();
}