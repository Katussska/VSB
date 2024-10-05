#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

// třída shaderloader pro načítání shaderů
class ShaderLoader
{
public:
    // načte shader z daného souboru
    static std::string loadShaderFromFile(const std::string &filePath); // statická metoda pro načtení shaderu
};

#endif // SHADER_LOADER_H