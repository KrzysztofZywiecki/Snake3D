#include "SnakeShader.h"

SnakeShader::SnakeShader(const char* vert, const char* geom, const char* frag)
{
    unsigned int vertex = CompileShader(vert, GL_VERTEX_SHADER);
    unsigned int geometry = CompileShader(geom, GL_GEOMETRY_SHADER);
    unsigned int fragment = CompileShader(frag, GL_FRAGMENT_SHADER);

    glAttachShader(shaderID, vertex);
    glAttachShader(shaderID, geometry);
    glAttachShader(shaderID, fragment);
    glLinkProgram(shaderID);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
    glDeleteShader(geometry);

    int linkStatus;
    glGetProgramiv(shaderID, GL_LINK_STATUS, &linkStatus);
    if(linkStatus != GL_TRUE)
    {
        std::cout<<"Failed to link program "<<vertex<<" + "<<fragment<<std::endl;
    }
    GetUniforms();
}

SnakeShader::~SnakeShader()
{
    //dtor
}

void SnakeShader::GetUniforms()
{
    cameraLocation = glGetUniformLocation(shaderID, "camera");
    this->value = glGetUniformLocation(shaderID, "value");
}

void SnakeShader::SetCamera()
{
    glUniformMatrix4fv(cameraLocation, 1, false, glm::value_ptr(Graphics::GetCamera()));
}

void SnakeShader::SetValue(float value)
{
    glUniform1f(this->value, value);
}
