#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>

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

	float indices[] = {-1.0f, -1.0f, 0.0f,
                        1.0f, -1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f};

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 3*sizeof(float), nullptr);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}
