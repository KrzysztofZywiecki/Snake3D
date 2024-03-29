#include "BasicShader.h"

void BasicShader::GetUniforms()
{
    cameraLocation = glGetUniformLocation(shaderID, "camera");
    colorLocation = glGetUniformLocation(shaderID, "u_color");
}

void BasicShader::SetCamera()
{
    glUniformMatrix4fv(cameraLocation, 1, false, glm::value_ptr(Graphics::GetCamera()));
}

void BasicShader::SetColor(float r, float g, float b)
{
    glUniform3f(colorLocation, r, g, b);
}

BasicShader::BasicShader(const char* vertex, const char* fragment)
{
    unsigned int vert = CompileShader(vertex, GL_VERTEX_SHADER);
    unsigned int frag = CompileShader(fragment, GL_FRAGMENT_SHADER);

    glAttachShader(shaderID, vert);
    glAttachShader(shaderID, frag);
    glLinkProgram(shaderID);

    glDeleteShader(vert);
    glDeleteShader(frag);

    int linkStatus;
    glGetProgramiv(shaderID, GL_LINK_STATUS, &linkStatus);
    if(linkStatus != GL_TRUE)
    {
        std::cout<<"Failed to link program "<<vertex<<" + "<<fragment<<std::endl;
    }
    GetUniforms();
}
