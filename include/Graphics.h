#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <stdexcept>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Graphics
{
public:
    static void Init();
    static void InitWindow(unsigned int width, unsigned int height, const char* title);
    static bool WindowShouldClose();
    static void UpdateDisplay();
private:
    static glm::mat4 camera;
    static GLFWwindow* window;
    static unsigned int width;
    static unsigned int height;
};

#endif // GRAPHICS_H
