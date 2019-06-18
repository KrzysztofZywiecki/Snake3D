#include <iostream>
#include "Graphics.h"
#include "Loader.h"
#include "Model.h"
#include "BasicShader.h"
#include "SnakeShader.h"


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


    std::vector<float> point = {0.0f, 0.0f, 0.0f};
    std::vector<unsigned int> ind = {0};

    Model cube = Loader::LoadToVAO(point, ind);
    glBindVertexArray(cube.GetVAO());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube.GetEBO());

	Model rect = Loader::LoadToVAO(vert, indices);
    Model grid = Loader::GenerateGrid(10, 10);
    //glBindVertexArray(grid.GetVAO());
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grid.GetEBO());
    //glBindVertexArray(rect.GetVAO());
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rect.GetEBO());
    //BasicShader shader("Shaders/basicVertex.txt", "Shaders/basicFragment.txt");
    //shader.Use();
    //shader.SetCamera();
    SnakeShader shader("Shaders/snakeVertex.txt", "Shaders/snakeGeometry.txt", "Shaders/snakeFragment.txt");
    shader.Use();
    shader.SetCamera();
    while(!Graphics::WindowShouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_POINTS, 0, 1);
        //glDrawElements(GL_POINTS, cube.GetVertexCount(), GL_UNSIGNED_INT, nullptr);

        Graphics::UpdateDisplay();
    }

    return 0;
}
