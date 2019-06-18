#ifndef SNAKESHADER_H
#define SNAKESHADER_H

#include <Shader.h>


class SnakeShader : public Shader
{
public:
    SnakeShader(const char* vert, const char* geom, const char* frag);
    ~SnakeShader();
    void GetUniforms();
    void SetCamera();
    void SetValue(float value);
private:
    unsigned int cameraLocation;
    unsigned int value;
};

#endif // SNAKESHADER_H
