#include <GLFW/glfw3.h>
#include "inputs.h"
#include "vec3.h"
#include <cmath>
#include <iostream>

vec3<float> CameraRotation;
vec3<float> CameraPosition = { 0, 200, -150 };
vec3<float> PlayerPosition;
vec3<float> PlayerRotation;
float speed = 1.0;

void PlayerControls(GLFWwindow* window_id, float &LastTime)
{
    float Time_Passed = glfwGetTime() - LastTime;
    LastTime = glfwGetTime();
    float radians = 0.01745329;

    if (glfwGetKey(window_id, GLFW_KEY_W) == GLFW_PRESS)
    {
        CameraPosition.z += cos(CameraRotation.y * radians) * Time_Passed * 200;
        CameraPosition.x += sin(CameraRotation.y * radians) * Time_Passed * 200;
        PlayerRotation.y = CameraRotation.y;
    }
    else if (glfwGetKey(window_id, GLFW_KEY_S) == GLFW_PRESS)
    {
        CameraPosition.z -= cos(CameraRotation.y * radians) * Time_Passed * 200;
        CameraPosition.x -= sin(CameraRotation.y * radians) * Time_Passed * 200;
        PlayerRotation.y = CameraRotation.y;
    }

    if (glfwGetKey(window_id, GLFW_KEY_D) == GLFW_PRESS)
    {
        CameraPosition.z += cos((CameraRotation.y + 90) * radians) * Time_Passed * 200;
        CameraPosition.x += sin((CameraRotation.y + 90) * radians) * Time_Passed * 200;
        PlayerRotation.y = CameraRotation.y;
    }
    else if (glfwGetKey(window_id, GLFW_KEY_A) == GLFW_PRESS)
    {
        CameraPosition.z -= cos((CameraRotation.y + 90) * radians) * Time_Passed * 200;
        CameraPosition.x -= sin((CameraRotation.y + 90) * radians) * Time_Passed * 200;
        PlayerRotation.y = CameraRotation.y;
    }

    if (glfwGetKey(window_id, GLFW_KEY_E) == GLFW_PRESS)
    {
        CameraPosition.y += Time_Passed*200;
    }
    else if (glfwGetKey(window_id, GLFW_KEY_Q) == GLFW_PRESS)
    {
        CameraPosition.y -= Time_Passed * 200;
    }
}

void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos)
{
    float xmov = xPos - 2560 / 2;
    float ymov = yPos - 1440 / 2;
    CameraRotation.x += ymov / 30;
    CameraRotation.y += xmov / 30;
    glfwSetCursorPos(window, 2560 / 2, 1440 / 2);
}

void KeyPress(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    
}

void InitialiseInputs(GLFWwindow* window_id)
{
    glfwSetCursorPosCallback(window_id, cursorPositionCallback);
    glfwSetInputMode(window_id, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetKeyCallback(window_id, KeyPress);
}
