#include "Graphics.h"

std::chrono::time_point<std::chrono::steady_clock> Graphics::previous;
float Graphics::time = 0.0f;
GLFWwindow* Graphics::window;
glm::mat4 Graphics::camera;
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

glm::mat4 Graphics::GetCamera()
{
    return camera;
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
    glEnable(GL_DEPTH_TEST);
    glDebugMessageCallback((GLDEBUGPROC)(callback), nullptr);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    const float angle = glm::radians(30.0f);
    glm::vec3 position = {0.0f, -1.5f, 0.8f};
    glm::vec3 direction = {0.0f, glm::cos(angle), -glm::sin(angle)};
    glm::vec3 up = {0.0f, glm::sin(angle), glm::cos(angle)};
	camera = glm::perspective(glm::radians(90.0f), (float)(width) / (float)(height), 0.1f, 10.0f) *
		glm::lookAt(position, direction, up);

    previous = std::chrono::steady_clock::now();
}

bool Graphics::WindowShouldClose()
{
    return glfwWindowShouldClose(window);
}

void Graphics::UpdateDisplay()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
    auto newTime = std::chrono::steady_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(newTime - previous).count();
    previous = newTime;
}

float Graphics::GetFrameTime()
{
    return time;
}

GLFWwindow* Graphics::GetWindowPtr()
{
    return window;
}
