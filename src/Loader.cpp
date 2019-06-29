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

void Loader::StoreDataInAttributeList(unsigned int attribute, unsigned int size, std::vector<float> data)
{
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(float), data.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(attribute);
    glVertexAttribPointer(attribute, size, GL_FLOAT, false, 3*sizeof(float), (void*)(0));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    vbos.push_back(vbo);
}

Model Loader::LoadToVAO(std::vector<float> positions, std::vector<unsigned int> indices)
{
    unsigned int vao = CreateVAO();
    StoreDataInAttributeList(0, 3, positions);
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

Model Loader::GenerateGrid(unsigned int x, unsigned int y)
{
    std::vector<float> positions;
    std::vector<unsigned int> indices;
    float width = 2.0f/(float)(x);
    float height = 2.0f/(float)(y);
    unsigned int counter = 0;

    for(int i = 0; i <= x; i++)
    {
        positions.push_back((float)(i)*width - 1.0f);
        positions.push_back(-1.0f);
        positions.push_back(0.0f);
        indices.push_back(counter);
        counter++;
        positions.push_back((float)(i)*width - 1.0f);
        positions.push_back(1.0f);
        positions.push_back(0.0f);
        indices.push_back(counter);
        counter++;
    }

    for(int i = 0; i <= y; i++)
    {
        positions.push_back(-1.0f);
        positions.push_back((float)(i)*height - 1.0f);
        positions.push_back(0.0f);
        indices.push_back(counter);
        counter++;
        positions.push_back(1.0f);
        positions.push_back((float)(i)*height - 1.0f);
        positions.push_back(0.0f);
        indices.push_back(counter);
        counter++;
    }

    return LoadToVAO(positions, indices);
}

Model Loader::GenerateWireCube(float x, float y, float z)
{
    std::vector<float> positions = {-x, -y, 0.0f,
                                    x, -y, 0.0f,
                                    x, y, 0.0f,
                                    -x, y, 0.0f,

                                    -x, -y, z*2.0f,
                                    x, -y, z*2.0f,
                                    x, y, z*2.0f,
                                    -x, y, z*2.0f};
    std::vector<unsigned int> indices = {0, 1, 1, 2, 2, 3, 3, 0,
                                        4, 5, 5, 6, 6, 7, 7, 4,
                                        0, 4, 1, 5, 2, 6, 3, 7};
    return LoadToVAO(positions, indices);
}

Model Loader::GenerateRectangle(float x, float y)
{
    std::vector<float> positions = {-x, -y, 0.0f,
                                    x, -y, 0.0f,
                                    x, y, 0.0f,
                                    -x, y, 0.0f};
    std::vector<unsigned int> indices = {0, 1, 2, 0, 2, 3};
    return LoadToVAO(positions, indices);
}

void Loader::UnbindVAO()
{
    glBindVertexArray(0);
}
