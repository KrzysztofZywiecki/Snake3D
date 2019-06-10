#ifndef BASICSHADER_H
#define BASICSHADER_H

#include "Shader.h"


class BasicShader : public Shader
{
public:
    BasicShader(const char* vertex, const char* fragment);
    void SetCamera();
    void GetUniforms();
private:
    unsigned int cameraLocation;
};

#endif // BASICSHADER_H
