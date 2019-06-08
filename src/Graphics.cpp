#include "Graphics.h"

GLFWwindow* Graphics::window;
unsigned int Graphics::height;
unsigned int Graphics::width;

void callback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	void* userParam) {
	std::cout << "OpenGL Error" << std::endl;
	std::cout << "[" << id << "]:" << message << " (" << type << ")";
}

void Graphics::Init()
{
    if(!glfwInit())
    {
        throw std::runtime_error("Couldn't initialize GLFW!");
    }
}

void Graphics::InitWindow(unsigned int width, unsigned int height, const char* title)
{
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if(window == nullptr)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create window!");
    }
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress));
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback((GLDEBUGPROC)(callback), nullptr);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

bool Graphics::WindowShouldClose()
{
    return glfwWindowShouldClose(window);
}

void Graphics::UpdateDisplay()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}
