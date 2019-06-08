#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <stdexcept>

class Graphics
{
public:
    static void Init();
    static void InitWindow(unsigned int width, unsigned int height, const char* title);
    static bool WindowShouldClose();
    static void UpdateDisplay();
private:
    static GLFWwindow* window;
    static unsigned int width;
    static unsigned int height;
};

#endif // GRAPHICS_H
