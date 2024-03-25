#include "CreateWindow.h"


GLFWwindow* createWindow(unsigned int width, unsigned int height)
{
    GLFWwindow* window;
    //// Initialize the library---
    if (!glfwInit())
    {
        std::cout << "tu dolboyeb\n";
    }

    //// Create a windowed mode window and its OpenGL context-------
    window = glfwCreateWindow(width, height, "Course Work", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        std::cout << "tu dolboyeb\n";
    }

    //// Make the window's context current-------
    glfwMakeContextCurrent(window);

    //// Init glue---------------------------
    if (glewInit() != GLEW_OK)
    {
        std::cout << "tu dolboyeb\n";
    }

    return window;
}