#include "Model.h"

Model::Model(unsigned int vao,unsigned int ebo , unsigned int vertexCount)
    :vao(vao), ebo(ebo), vertexCount(vertexCount)
{
}

Model::~Model()
{
}

const unsigned int Model::GetEBO() const
{
    return ebo;
}

const unsigned int Model::GetVAO() const
{
    return vao;
}

const unsigned int Model::GetVertexCount() const
{
    return vertexCount;
}
