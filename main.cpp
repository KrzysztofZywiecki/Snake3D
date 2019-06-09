#include <iostream>
#include "Graphics.h"
#include "Loader.h"
#include "Model.h"
#include "BasicShader.h"


using namespace std;



int main()
{
    Graphics::Init();
    Graphics::InitWindow(800, 600, "magister");

	std::vector<float> vert = {-0.5f, -0.5f, 0.0f,
                                0.5f, -0.5f, 0.0f,
                                0.5f, 0.5f, 0.0f,
                                -0.5f, 0.5f, 0.0f};
    std::vector<unsigned int> indices = {0, 1, 2, 0, 2, 3};

	Model rect = Loader::LoadToVAO(vert, indices);

    glBindVertexArray(rect.GetVAO());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rect.GetEBO());

    BasicShader shader("Shaders/basicVertex.txt", "Shaders/basicFragment.txt");
    shader.Use();

    while(!Graphics::WindowShouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, rect.GetVertexCount(), GL_UNSIGNED_INT, nullptr);

        Graphics::UpdateDisplay();
    }

    return 0;
}
