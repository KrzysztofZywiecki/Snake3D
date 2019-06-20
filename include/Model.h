#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>

class Model
{
public:
    Model(unsigned int vao, unsigned int ebo, unsigned int vertexCount);
    ~Model();

    const unsigned int GetEBO() const;
    const unsigned int GetVertexCount() const;
    const unsigned int GetVAO() const;
    void Bind() const;
private:
    unsigned int vao;
    unsigned int ebo;
    unsigned int vertexCount;
};

#endif // MODEL_H
