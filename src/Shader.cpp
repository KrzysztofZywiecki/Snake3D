#include "Shader.h"

#define SOURCE_LEN 2048

Shader::Shader()
{
    shaderID = glCreateProgram();
}

Shader::~Shader()
{
    glDeleteProgram(shaderID);
}

void Shader::GetUniforms()
{
}

void Shader::Use()
{
    glUseProgram(shaderID);
}

unsigned int Shader::CompileShader(const char* filename, unsigned int type)
{
    unsigned int shader = glCreateShader(type);
    std::unique_ptr<char> source(new char[SOURCE_LEN]);
    std::ifstream file(filename);
    if(!file)
    {
        std::cout<<"Couldn't open file "<<filename<<std::endl;
        glDeleteShader(shader);
        return 0;
    }

    file.get(source.get(), SOURCE_LEN, 0);
    char* src = source.get();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE)
    {
        char message[1024];
        glGetShaderInfoLog(shader, 1024, &status, message);
        std::cout<<message<<std::endl;
    }

    return shader;
}
