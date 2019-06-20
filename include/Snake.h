#ifndef SNAKE_H
#define SNAKE_H
#include <vector>
#include "Loader.h"
#include "Model.h"
#include "Graphics.h"


class Snake
{
public:
    Snake(unsigned int grid_x, unsigned int grid_y);
    virtual ~Snake();

    void Draw();

private:
    float x;
    float y;
    unsigned int grid_x;
    unsigned int grid_y;
    unsigned int instances;

    std::vector<float> segments;
    bool* occupied;
    void InsertInstance(int x, int y);
    Model globalCube;
};

#endif // SNAKE_H
