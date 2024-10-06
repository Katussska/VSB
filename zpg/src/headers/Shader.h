#pragma once

#include <string>
#include <unordered_map>

// struktura pro uchovani zdroju shaderu
struct ShaderProgramSource
{
    std::string VertexSource;   // zdroj vertex shaderu
    std::string FragmentSource; // zdroj fragment shaderu
};

// trida pro spravu shaderu
class Shader
{
private:
    std::string m_FilePath;                                      // cesta k souboru shaderu
    unsigned int m_RendererID;                                   // identifikator shaderu pro renderer
    std::unordered_map<std::string, int> m_UniformLocationCache; // cache pro uniform location

public:
    // konstruktor inicializuje shader s cestou k souboru
    Shader(const std::string &filepath);

    // destruktor pro uvolneni shaderu
    ~Shader();

    // metoda pro aktivaci shaderu
    void Bind() const;

    // metoda pro deaktivaci shaderu
    void Unbind() const;

    // nastaveni uniform pro integer
    void SetUniform1i(const std::string &name, float value);

    // nastaveni uniform pro vec4
    void SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3);

private:
    // kompilace shaderu podle typu a zdroje
    unsigned int CompileShader(unsigned int type, const std::string &source);

    // vytvoreni shaderu ze zdroju vertex a fragment shaderu
    unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader);

    // parsovani shaderu ze souboru
    ShaderProgramSource ParseShader(const std::string &filepath);

    // ziskani location uniformu
    int GetUniformLocation(const std::string &name);
};
