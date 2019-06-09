#ifndef SHADER_H
#define SHADER_H
#include <Graphics.h>
#include <memory>
#include <fstream>

class Shader
{
public:
    Shader();
    ~Shader();
    virtual void GetUniforms();
    void Use();
protected:
    static unsigned int CompileShader(const char* filename, unsigned int type);
    unsigned int shaderID;
};

#endif // SHADER_H
