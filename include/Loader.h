#ifndef LOADER_H
#define LOADER_H
#include <list>
#include <vector>
#include <glad/glad.h>
#include "Model.h"

class Loader
{
public:
    Loader();

    static unsigned int CreateVAO();
    static unsigned int CreateEBO(std::vector<unsigned int> indices);
    static void StoreDataInAttributeList(unsigned int attribute, std::vector<float> data);
    static Model LoadToVAO(std::vector<float> positions, std::vector<unsigned int> indices);
    static void UnbindVAO();
private:
    static std::list<unsigned int> vaos;
    static std::list<unsigned int> vbos;
};

#endif // LOADER_H
