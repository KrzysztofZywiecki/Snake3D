#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <stdexcept>
#include <chrono>

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
    static glm::mat4 GetCamera();
    static float GetFrameTime();
    static GLFWwindow* GetWindowPtr();
private:
    static float time;
    static std::chrono::time_point<std::chrono::steady_clock> previous;
    static glm::mat4 camera;
    static GLFWwindow* window;
    static unsigned int width;
    static unsigned int height;
};

#endif // GRAPHICS_H
