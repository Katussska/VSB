#include "headers/ShaderLoader.h"

// načte shader z daného souboru
std::string ShaderLoader::loadShaderFromFile(const std::string &filePath)
{
    std::ifstream shaderFile(filePath); // otevření souboru se shaderem
    if (!shaderFile.is_open())          // kontrola, zda je soubor otevřen
    {
        throw std::runtime_error("Could not open shader file: " + filePath); // vyhození výjimky, pokud se soubor nepodařilo otevřít
    }

    std::stringstream shaderStream;     // vytvoření streamu pro načtení shaderu
    shaderStream << shaderFile.rdbuf(); // načtení obsahu souboru do streamu
    shaderFile.close();                 // zavření souboru
    return shaderStream.str();          // vrátí načtený shader jako řetězec
}
