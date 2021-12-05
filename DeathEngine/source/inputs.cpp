#include <GLFW/glfw3.h>
#include "inputs.h"
#include "window.h"
#include "vec3.h"
#include <cmath>
#include <iostream>

vec3<float> CameraRotation;
vec3<float> CameraPosition = { 0, 0, 0 };
vec3<float> PlayerPosition;
vec3<float> PlayerRotation;
float speed = 1;
float MouseSensitivity = 0.1;

bool PlayerControls(window win, float &LastTime)
{
    float Time_Passed = glfwGetTime() - LastTime;
    LastTime = glfwGetTime();
    float radians = 0.01745329;

    if (glfwGetKey(win.window_id, GLFW_KEY_W) == GLFW_PRESS)
    {
        CameraPosition.z += cos(CameraRotation.y * radians) * Time_Passed * speed;
        CameraPosition.x += sin(CameraRotation.y * radians) * Time_Passed * speed;
        PlayerRotation.y = CameraRotation.y;
    }
    else if (glfwGetKey(win.window_id, GLFW_KEY_S) == GLFW_PRESS)
    {
        CameraPosition.z -= cos(CameraRotation.y * radians) * Time_Passed * speed;
        CameraPosition.x -= sin(CameraRotation.y * radians) * Time_Passed * speed;
        PlayerRotation.y = CameraRotation.y;
    }

    if (glfwGetKey(win.window_id, GLFW_KEY_D) == GLFW_PRESS)
    {
        CameraPosition.z += cos((CameraRotation.y + 90) * radians) * Time_Passed * speed;
        CameraPosition.x += sin((CameraRotation.y + 90) * radians) * Time_Passed * speed;
        PlayerRotation.y = CameraRotation.y;
    }
    else if (glfwGetKey(win.window_id, GLFW_KEY_A) == GLFW_PRESS)
    {
        CameraPosition.z -= cos((CameraRotation.y + 90) * radians) * Time_Passed * speed;
        CameraPosition.x -= sin((CameraRotation.y + 90) * radians) * Time_Passed * speed;
        PlayerRotation.y = CameraRotation.y;
    }

    if (glfwGetKey(win.window_id, GLFW_KEY_E) == GLFW_PRESS)
    {
        CameraPosition.y += Time_Passed * speed;
    }
    else if (glfwGetKey(win.window_id, GLFW_KEY_Q) == GLFW_PRESS)
    {
        CameraPosition.y -= Time_Passed * speed;
    }

    if (glfwGetKey(win.window_id, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        return true;
    }

    return false;
}

float yrot, xrot;
float mposy, mposx;
bool firstpress = true;

void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos)
{
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (state == GLFW_PRESS)
    {
        if (firstpress == true)
        {
            yrot = CameraRotation.y;
            xrot = CameraRotation.x;
            mposy = yPos;
            mposx = xPos;
            firstpress = false;
        }
        CameraRotation.y = yrot + (xPos - mposx) * MouseSensitivity;
        CameraRotation.x = xrot + (yPos - mposy) * MouseSensitivity;
    }
    else if (state == GLFW_RELEASE)
    {
        firstpress = true;
    }
}

void KeyPress(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    
}

void InitialiseInputs(window win)
{
    glfwSetCursorPosCallback(win.window_id, cursorPositionCallback);
    //glfwSetInputMode(win.window_id, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetKeyCallback(win.window_id, KeyPress);
}
