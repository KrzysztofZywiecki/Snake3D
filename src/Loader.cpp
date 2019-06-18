#include "Loader.h"

std::list<unsigned int> Loader::vaos;
std::list<unsigned int> Loader::vbos;

Loader::Loader()
{
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
