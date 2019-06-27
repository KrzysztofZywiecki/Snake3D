#include "Ant.h"

Ant::Ant(unsigned int grid_x, unsigned int grid_y, Model cube, Model rect, BasicShader shader)
    :x(2.0f/(float)(grid_x)), y(2.0f/(float)(grid_y)),
    grid_x(grid_x), grid_y(grid_y),
    globalCube(Loader::GenerateWireCube(1.0f/(float)grid_x, 1.0f/(float)grid_y, 1.0f/(float)grid_y)),
     globalRectangle(Loader::GenerateRectangle(1.0f/(float)grid_x, 1.0f/(float)grid_y)), shader(shader)
{
    srand(time(NULL));
    glBindVertexArray(globalCube.GetVAO());
    glGenBuffers(1, &position);
    glBindBuffer(GL_ARRAY_BUFFER, position);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 2*sizeof(float), (void*)(0));
    glVertexAttribDivisor(1, 1);

    glBindVertexArray(globalRectangle.GetVAO());
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 2*sizeof(float), (void*)(0));
    glVertexAttribDivisor(1, 1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Ant::ResetPosition(bool* occupied)
{
    unsigned int pos;
    do
    {
        pos = rand()%(grid_x*grid_y);
    }while(occupied[pos]);
    unsigned int x = pos/grid_y;

    translation[0] = -1.0f+this->x/2.0f + (float)(x)*this->x;
    translation[1] = -1.0f+this->y/2.0f + (float)(pos%grid_y)*this->y;
    SetData();
}

void Ant::SetData()
{
    glBindBuffer(GL_ARRAY_BUFFER, position);
    glBufferData(GL_ARRAY_BUFFER, 2*sizeof(float), translation, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Ant::Draw()
{
    shader.Use();
    globalRectangle.Bind();
    shader.SetColor(1.0f, 0.0f, 0.0f);
    glDrawElementsInstanced(GL_TRIANGLES, globalRectangle.GetVertexCount(),
    GL_UNSIGNED_INT, nullptr, 1);

    globalCube.Bind();
    glDrawElementsInstanced(GL_LINES, globalCube.GetVertexCount(),
    GL_UNSIGNED_INT, nullptr, 1);
}

Ant::~Ant()
{

}
