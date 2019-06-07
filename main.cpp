#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "Loader.h"
#include "Model.h"

using namespace std;

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

int main()
{
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 600, "Magister", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress));
    glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback((GLDEBUGPROC)callback, nullptr);

	std::vector<float> vert = {-0.5f, -0.5f, 0.0f,
                                0.5f, -0.5f, 0.0f,
                                0.5f, 0.5f, 0.0f,
                                -0.5f, 0.5f, 0.0f};
    std::vector<unsigned int> indices = {0, 1, 2, 0, 2, 3};

	Model rect = Loader::LoadToVAO(vert, indices);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glBindVertexArray(rect.GetVAO());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rect.GetEBO());

    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, rect.GetVertexCount(), GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}
