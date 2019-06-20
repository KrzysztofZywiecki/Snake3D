#ifndef LOADER_H
#define LOADER_H
#include <list>
#include <vector>
#include "Graphics.h"
#include "Model.h"

class Loader
{
public:
    Loader();

    static unsigned int CreateVAO();
    static unsigned int CreateEBO(std::vector<unsigned int> indices);
    static void StoreDataInAttributeList(unsigned int attribute, unsigned int size, std::vector<float> data);
    static void SetDivisor(Model model, unsigned int attribute);
    static void UpdateBufferData(std::vector<float> data);

    static Model LoadToVAO(std::vector<float> positions, std::vector<unsigned int> indices);
    static Model GenerateGrid(unsigned int x, unsigned int y);
    static Model GenerateWireCube(float x, float y, float z);
private:
    static void UnbindVAO();
    static std::list<unsigned int> vaos;
    static std::list<unsigned int> vbos;
};

#endif // LOADER_H
