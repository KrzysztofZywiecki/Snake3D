#include <iostream>
#include "Graphics.h"
#include "Loader.h"
#include "Model.h"
#include "BasicShader.h"
#include "Snake.h"


using namespace std;



int main()
{
    Graphics::Init();
    Graphics::InitWindow(800, 600, "magister");

	std::vector<float> vert = {-1.0, -1.0f, 0.0f,
                                1.0f, -1.0f, 0.0f,
                                1.0f, 1.0f, 0.0f,
                                -1.0f, 1.0f, 0.0f};
    std::vector<unsigned int> indices = {0, 1, 2, 0, 2, 3};

	Model rect = Loader::LoadToVAO(vert, indices);

    glBindVertexArray(rect.GetVAO());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rect.GetEBO());
    BasicShader shader("Shaders/basicVertex.txt", "Shaders/basicFragment.txt");
    shader.Use();
    shader.SetCamera();
    shader.SetColor(1.0f, 1.0f, 1.0f);

    Model grid = Loader::GenerateGrid(9, 9);
    Model cube = Loader::GenerateWireCube(1.0f, 1.0f, 1.0f);
    Snake snake(9, 9);
    while(!Graphics::WindowShouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);
        //glDrawElements(GL_TRIANGLES, rect.GetVertexCount(), GL_UNSIGNED_INT, nullptr);
        grid.Bind();
        shader.SetColor(1.0f, 0.0f, 0.0f);
        glDrawElements(GL_LINES, grid.GetVertexCount(), GL_UNSIGNED_INT, nullptr);
        cube.Bind();
        shader.SetColor(0.0f, 1.0f, 0.0f);
        glDrawElements(GL_LINES, cube.GetVertexCount(), GL_UNSIGNED_INT, nullptr);

        snake.Update(Graphics::GetFrameTime());
        snake.Draw();

        Graphics::UpdateDisplay();
        Sleep(10);
    }

    return 0;
}
