#include "Snake.h"

Snake::Snake(unsigned int grid_x, unsigned int grid_y, BasicShader shader)
    :x(2.0f/(float)(grid_x)), y(2.0f/(float)(grid_y)),
    grid_x(grid_x), grid_y(grid_y), direction(Direction::RIGHT), selected(Direction::RIGHT),
     globalCube(Loader::GenerateWireCube(1.0f/(float)grid_x, 1.0f/(float)grid_y, 1.0f/(float)grid_y)),
     globalRectangle(Loader::GenerateRectangle(1.0f/(float)grid_x, 1.0f/(float)grid_y)), shader(shader),
     ant(grid_x, grid_y, globalCube, globalRectangle, shader)
{
    occupied = new bool[grid_x * grid_y];
    memset(occupied, 0, grid_x * grid_y);

    glBindVertexArray(globalCube.GetVAO());
    glGenBuffers(1, &instances);
    glBindBuffer(GL_ARRAY_BUFFER, instances);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 2*sizeof(float), (void*)(0));
    glVertexAttribDivisor(1, 1);

    glBindVertexArray(globalRectangle.GetVAO());
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 2*sizeof(float), (void*)(0));
    glVertexAttribDivisor(1, 1);
    ant.ResetPosition(occupied);
    InsertInstance(0, 0);
    InsertInstance(-1, 0);
    InsertInstance(-2, 0);
}

void Snake::InsertInstance(int x, int y)
{
    segments.push_back((float)x * this->x);
    segments.push_back((float)y * this->y);
    segmentCoords.push_back(grid_x/2 + x);
    segmentCoords.push_back(grid_y/2 + y);
    Access(grid_x/2 + x, grid_y/2 + y) = true;
    UpdateInstances();
}

void Snake::Draw()
{
    shader.Use();
    globalRectangle.Bind();
    shader.SetColor(1.0f, 1.0f, 0.0f);
    glDrawElementsInstanced(GL_TRIANGLES, globalRectangle.GetVertexCount(),
    GL_UNSIGNED_INT, nullptr, segments.size()/2);

    shader.Use();
    globalCube.Bind();
    shader.SetColor(0.0f, 1.0f, 0.0f);
    glDrawElementsInstanced(GL_LINES, globalCube.GetVertexCount(),
    GL_UNSIGNED_INT, nullptr, segments.size()/2);
    ant.Draw();
}

void Snake::Update(float time)
{
    timer += time;
    GetKeys();
    while(timer > difficulty)
    {
        direction = selected;
        MoveTail();
        MoveHead();
        if(ant.Collision(segmentCoords[0], segmentCoords[1]))
        {
            InsertInstance(segmentCoords[segmentCoords.size()-2]-grid_x/2, segmentCoords[segmentCoords.size()-1]-grid_y/2);
            ant.ResetPosition(occupied);
        }
        timer -= difficulty;
    }
}

void Snake::MoveHead()
{
    switch(direction)
    {
    case UP:
        segments[1] += y;
        segmentCoords[1]++;
        break;
    case DOWN:
        segments[1] -= y;
        segmentCoords[1]--;
        break;
    case LEFT:
        segments[0] -= x;
        segmentCoords[0]--;
        break;
    case RIGHT:
        segments[0] += x;
        segmentCoords[0]++;
        break;
    }
    if(segmentCoords[0]>=grid_x || segmentCoords[0]<0 || segmentCoords[1]>=grid_y || segmentCoords[1]<0)
    {
        exit(1);
    }
    if(Access(segmentCoords[0], segmentCoords[1]))
    {
        exit(2);
    }
    Access(segmentCoords[0], segmentCoords[1]) = true;
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
    if(glfwGetKey(Graphics::GetWindowPtr(), GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        if(direction != Direction::UP)
            selected = Direction::DOWN;
    }
    if(glfwGetKey(Graphics::GetWindowPtr(), GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        if(direction != Direction::RIGHT)
            selected = Direction::LEFT;
    }
    if(glfwGetKey(Graphics::GetWindowPtr(), GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        if(direction != Direction::LEFT)
            selected = Direction::RIGHT;
    }
}

void Snake::MoveTail()
{
    Access(segmentCoords[segmentCoords.size() - 2], segmentCoords[segmentCoords.size() - 1]) = false;
    for(int i=0; i<segmentCoords.size(); i+=2)
    {
        std::cout<<"["<<segmentCoords[i]<<", "<<segmentCoords[i+1]<<"]"<<std::endl;
    }
    for(int i=segments.size()/2; i>0; i--)
    {
        segments[i*2] = segments[(i-1)*2];
        segments[i*2 + 1] = segments[(i-1)*2 + 1];

        segmentCoords[i*2] = segmentCoords[(i-1)*2];
        segmentCoords[i*2 + 1] = segmentCoords[(i-1)*2 + 1];
    }
    UpdateInstances();
}

bool& Snake::Access(int x, int y)
{
    return occupied[x*grid_y + y];
}

Snake::~Snake()
{
    delete[] occupied;
}
