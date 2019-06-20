#ifndef BASICSHADER_H
#define BASICSHADER_H

#include "Shader.h"


class BasicShader : public Shader
{
public:
    BasicShader(const char* vertex, const char* fragment);
    void SetCamera();
    void SetColor(float r, float g, float b);
    void GetUniforms();
private:
    unsigned int cameraLocation;
    unsigned int colorLocation;
};

#endif // BASICSHADER_H
