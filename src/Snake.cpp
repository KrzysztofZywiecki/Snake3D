#include "Snake.h"

Snake::Snake(unsigned int grid_x, unsigned int grid_y)
    :x(1.0f/(float)(grid_x)), y(1.0f/(float)(grid_y)),
    grid_x(grid_x), grid_y(grid_y),
     globalCube(Loader::GenerateWireCube(x, y, x))
{
    occupied = new bool[grid_x * grid_y];
    memset(occupied, 0, grid_x * grid_y);

    glBindVertexArray(globalCube.GetVAO());
    glGenBuffers(1, &instances);
    glBindBuffer(GL_ARRAY_BUFFER, instances);
    glBufferData(GL_ARRAY_BUFFER, segments.size()*sizeof(float), segments.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 2*sizeof(float), (void*)(0));
    glVertexAttribDivisor(1, 1);

    InsertInstance(0, 0);
    InsertInstance(1, 0);
}

void Snake::InsertInstance(int x, int y)
{
    segments.push_back((float)(x - grid_x/2) * this->x);
    segments.push_back((float)(y - grid_y/2) * this->y);
    glBindBuffer(GL_ARRAY_BUFFER, instances);
    glBufferData(GL_ARRAY_BUFFER, segments.size() * sizeof(float), segments.data(), GL_STATIC_DRAW);
}

void Snake::Draw()
{
    globalCube.Bind();
    glDrawElementsInstanced(GL_LINES, globalCube.GetVertexCount(),
    GL_UNSIGNED_INT, nullptr, segments.size()/2);
}

Snake::~Snake()
{
    delete[] occupied;
}