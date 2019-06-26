#ifndef SNAKE_H
#define SNAKE_H
#include <vector>
#include "Loader.h"
#include "Model.h"
#include "Graphics.h"

enum Direction
{ UP, DOWN, LEFT, RIGHT };

class Snake
{
public:
    Snake(unsigned int grid_x, unsigned int grid_y);
    virtual ~Snake();

    void SwitchDirection(Direction direction);

    void Draw();
    void Update(float time);
private:
    float x;
    float y;
    unsigned int grid_x;
    unsigned int grid_y;
    unsigned int instances;

    const float difficulty = 300.0f;
    Direction direction;
    Direction selected;
    float timer = 0.0f;
    std::vector<float> segments;
    bool* occupied;
    void InsertInstance(int x, int y);
    Model globalCube;

    void GetKeys();
    void UpdateInstances();
    void MoveTail();
    void MoveHead();
};

#endif // SNAKE_H
