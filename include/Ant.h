#ifndef ANT_H
#define ANT_H
#include <cstdlib>
#include "Graphics.h"
#include "Loader.h"
#include "BasicShader.h"

class Ant
{
public:
    Ant(unsigned int grid_x, unsigned int grid_y, Model cube, Model rect, BasicShader shader);
    ~Ant();

    bool Collision(unsigned int x, unsigned int y);
    void Draw();
    void ResetPosition(bool* occupied);
private:
    unsigned int pos_x;
    unsigned int pos_y;
    unsigned int grid_x;
    unsigned int grid_y;
    float x;
    float y;
    float translation[2];
    unsigned int position;
    BasicShader shader;
    Model globalCube;
    Model globalRectangle;
    void SetData();
};

#endif // ANT_H
