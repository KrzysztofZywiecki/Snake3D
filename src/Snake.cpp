#include "Snake.h"

Snake::Snake(unsigned int grid_x, unsigned int grid_y)
    :x(2.0f/(float)(grid_x)), y(2.0f/(float)(grid_y)),
    grid_x(grid_x), grid_y(grid_y), direction(Direction::RIGHT),
     globalCube(Loader::GenerateWireCube(1.0f/(float)grid_x, 1.0f/(float)grid_y, 1.0f/(float)grid_y))
{
    occupied = new bool[grid_x * grid_y];
    memset(occupied, 0, grid_x * grid_y);

    glBindVertexArray(globalCube.GetVAO());
    glGenBuffers(1, &instances);
    glBindBuffer(GL_ARRAY_BUFFER, instances);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 2*sizeof(float), (void*)(0));
    glVertexAttribDivisor(1, 1);
    InsertInstance(0, 0);
    InsertInstance(-1, 0);
    InsertInstance(-2, 0);
}

void Snake::InsertInstance(int x, int y)
{
    segments.push_back((float)x * this->x);
    segments.push_back((float)y * this->y);
    glBindBuffer(GL_ARRAY_BUFFER, instances);
    glBufferData(GL_ARRAY_BUFFER, segments.size() * sizeof(float), segments.data(), GL_STATIC_DRAW);
}

void Snake::Draw()
{
    globalCube.Bind();
    glDrawElementsInstanced(GL_LINES, globalCube.GetVertexCount(),
    GL_UNSIGNED_INT, nullptr, segments.size()/2);
}

void Snake::Update(float time)
{
    timer += time;
    while(timer > difficulty)
    {
        MoveHead();

        timer -= difficulty;
    }
}

void Snake::MoveHead()
{
    switch(direction)
    {
    case UP:
        segments[1] += y;
        break;
    case DOWN:
        segments[1] -= y;
        break;
    case LEFT:
        segments[0] -= x;
        break;
    case RIGHT:
        segments[0] += x;
        break;
    }
    UpdateInstances();
}

void Snake::UpdateInstances()
{
    glBindBuffer(GL_ARRAY_BUFFER, instances);
    glBufferData(GL_ARRAY_BUFFER, segments.size()*sizeof(float), segments.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Snake::GetKeys()
{
    if(glfwGetKey(Graphics::GetWindowPtr(), GLFW_KEY_UP) == GLFW_PRESS)
    {
        if(direction != Direction::DOWN)
            selected = Direction::UP;
    }
}

Snake::~Snake()
{
    delete[] occupied;
}
