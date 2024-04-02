//과제물 프로젝트명: Lecture04_HW
//idle : 화면색 검정색으로 clear
//마우스 오른쪽 KeyDown하면 : 빨간색
//마우스 오른쪽 KeyUp하면 : 원상복구
//마우스 왼쪽 KeyDown하면 : 녹색
//마우스 왼쪽 KeyUp하면 : 원상복구
//마우스 오른쪽 KeyDown하고 드래그 중이면 : 파랑색
//마우스 왼쪽 KeyDown하고 드래그 중이면 : 마젠타색

//https://www.glfw.org/
#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>

bool leftMouseDown = false;
bool rightMouseDown = false;
bool draggingLeft = false;
bool draggingRight = false;

void errorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            leftMouseDown = true;
            draggingLeft = true;
            glClearColor(0.0f, 1.0f, 0.0f, 1.0f); // Green background color
        }
        else if (action == GLFW_RELEASE)
        {
            leftMouseDown = false;
            draggingLeft = false;
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Default background color
        }
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if (action == GLFW_PRESS)
        {
            rightMouseDown = true;
            draggingRight = true;
            glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // Red background color
        }
        else if (action == GLFW_RELEASE)
        {
            rightMouseDown = false;
            draggingRight = false;
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Default background color
        }
    }

    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
}

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (draggingLeft)
    {
        glClearColor(1.0f, 0.0f, 1.0f, 1.0f); // Magenta background color
    }
    else if (draggingRight)
    {
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // Blue background color
    }
    else if (leftMouseDown)
    {
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f); // Green background color
    }
    else if (rightMouseDown)
    {
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // Red background color
    }
    else
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Default background color
    }

    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
}

void mouseDragCallback(GLFWwindow* window, double xpos, double ypos)
{
    // Check if the left mouse button is pressed and dragging
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        draggingLeft = true;
    }
    else
    {
        draggingLeft = false;
        if (leftMouseDown) {
            glClearColor(0.0f, 1.0f, 0.0f, 1.0f); // Green background color
        }
    }

    // Check if the right mouse button is pressed and dragging
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        draggingRight = true;
    }
    else
    {
        draggingRight = false;
        if (rightMouseDown) {
            glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // Red background color
        }
    }
}

int main(void)
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(1280, 768, "Lecture04_HW", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}