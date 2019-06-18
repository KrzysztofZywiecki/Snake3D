#include "Loader.h"

std::list<unsigned int> Loader::vaos;
std::list<unsigned int> Loader::vbos;

Loader::Loader()
{
}

Model Loader::GenerateGrid(unsigned int x, unsigned int y)
{
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    float width = 2.0f/(float)(x);
    float height = 2.0f/(float)(y);

    unsigned int counter = 0;

    for(int i=0; i<=x; i++)
    {
        vertices.push_back(-1.0f + width * (float)(i));
        vertices.push_back(-1.0f);
        vertices.push_back(0.0f);
        indices.push_back(counter);
        counter++;
        vertices.push_back(-1.0f + width * (float)(i));
        vertices.push_back(1.0f);
        vertices.push_back(0.0f);
        indices.push_back(counter);
        counter++;
    }
    for(int i=0; i<=y; i++)
    {
        vertices.push_back(-1.0f);
        vertices.push_back(-1.0f + height*(float)(i));
        vertices.push_back(0.0f);
        indices.push_back(counter);
        counter++;
        vertices.push_back(1.0f);
        vertices.push_back(-1.0f + height*(float)(i));
        vertices.push_back(0.0f);
        indices.push_back(counter);
        counter++;
    }

    return LoadToVAO(vertices, indices);
}

unsigned int Loader::CreateVAO()
{
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    vaos.push_back(vao);
    return vao;
}

void Loader::StoreDataInAttributeList(unsigned int attribute, std::vector<float> data)
{
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(float), data.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(attribute);
    glVertexAttribPointer(attribute, 3, GL_FLOAT, false, 3*sizeof(float), (void*)(0));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    vbos.push_back(vbo);
}

Model Loader::LoadToVAO(std::vector<float> positions, std::vector<unsigned int> indices)
{
    unsigned int vao = CreateVAO();
    StoreDataInAttributeList(0, positions);
    unsigned int ebo = CreateEBO(indices);
    UnbindVAO();
    return Model(vao, ebo, indices.size());
}

unsigned int Loader::CreateEBO(std::vector<unsigned int> indices)
{
    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                  indices.size()*sizeof(unsigned int),
                  indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    vbos.push_back(ebo);
    return ebo;
}

void Loader::UnbindVAO()
{
    glBindVertexArray(0);
}
