#include "headers/Shader.h"
#include "headers/Renderer.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <GL/glew.h>

// konstruktor shaderu, nacita shader z filepath a vytvori shaderovy program
Shader::Shader(const std::string &filepath) : m_FilePath(filepath), m_RendererID(0)
{
    ShaderProgramSource source = ParseShader(filepath);                      // parsuje zdroj shaderu z file
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource); // vytvori shaderovy program z vertex a fragment shaderu
}

// destruktor, maze shaderovy program pri ruseni objektu
Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID)); // smaze shaderovy program na zaklade jeho id
}

// funkce binduje shaderovy program, aby ho bylo mozne pouzit
void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID)); // aktivuje shaderovy program podle jeho id
}

// funkce unbinduje shaderovy program, kdyz uz neni treba
void Shader::Unbind() const
{
    GLCall(glUseProgram(0)); // deaktivuje aktualni shaderovy program
}

// funkce kompiluje shader, kontroluje chyby a vraci id shaderu
unsigned int Shader::CompileShader(unsigned int type, const std::string &source)
{
    GLCall(unsigned int id = glCreateShader(type)); // vytvori shader podle typu (vertex nebo fragment)
    const char *src = source.c_str();               // prevede zdrojovy kod shaderu na c-string
    GLCall(glShaderSource(id, 1, &src, nullptr));   // priradi zdrojovy kod shaderu
    GLCall(glCompileShader(id));                    // kompiluje shader

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result)); // zjistuje, zda kompilace probehla uspesne
    if (result == GL_FALSE)                                // pokud kompilace selhala
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));   // zjisti delku chybove zpravy
        char *message = (char *)alloca(length * sizeof(char));    // alokuje pamet pro chybovou zpravu
        GLCall(glGetShaderInfoLog(id, length, &length, message)); // nacte chybovou zpravu
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteShader(id)); // smaze shader, pokud kompilace selhala
        return 0;
    }

    return id; // vrati id shaderu, pokud kompilace byla uspesna
}

// funkce parsuje zdroj shaderu z file na vertex a fragment shader casti
ShaderProgramSource Shader::ParseShader(const std::string &filepath)
{
    std::ifstream stream(filepath); // otevre soubor pro cteni

    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];            // vytvori 2 stringstreamy pro vertex a fragment shader
    ShaderType type = ShaderType::NONE; // inicializuje typ shaderu na NONE

    while (getline(stream, line)) // cte soubor radek po radku
    {
        if (line.find("#shader") != std::string::npos) // pokud se v radku nachazi #shader
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX; // urci, ze nasledujici kod je vertex shader
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT; // urci, ze nasledujici kod je fragment shader
        }
        else
            ss[(int)type] << line << '\n'; // prida radek do odpovidajiciho shader streamu
    }

    return {ss[0].str(), ss[1].str()}; // vrati zdrojovy kod pro vertex a fragment shader
}

// funkce vytvori shaderovy program z vertex a fragment shaderu
unsigned int Shader::CreateShader(const std::string &vertexShader, const std::string &fragmentShader)
{
    GLCall(unsigned int program = glCreateProgram());                    // vytvori novy shaderovy program
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);     // kompiluje vertex shader
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader); // kompiluje fragment shader

    GLCall(glAttachShader(program, vs)); // pripoji vertex shader k programu
    GLCall(glAttachShader(program, fs)); // pripoji fragment shader k programu
    GLCall(glLinkProgram(program));      // linkuje program
    GLCall(glValidateProgram(program));  // validuje program

    GLCall(glDeleteShader(vs)); // smaze vertex shader po linkovani
    GLCall(glDeleteShader(fs)); // smaze fragment shader po linkovani

    return program; // vrati id programu
}

// funkce nastavi uniformu typu float podle jmena
void Shader::SetUniform1i(const std::string &name, float value)
{
    GLCall(glUniform1f(GetUniformLocation(name), value)); // nastavi uniformu na hodnotu
}

// funkce nastavi uniformu typu vec4 podle jmena
void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3)); // nastavi uniformu na ctyri hodnoty
}

// funkce ziska lokaci uniformy podle jmena, pokud je jiz v cache, vrati ji
int Shader::GetUniformLocation(const std::string &name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) // kontroluje, zda je uniforma v cache
        return m_UniformLocationCache[name];                               // vrati lokaci z cache

    GLCall(unsigned int location = glGetUniformLocation(m_RendererID, name.c_str())); // ziska lokaci uniformy

    if (location == -1) // pokud uniforma neexistuje
        std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

    m_UniformLocationCache[name] = location; // ulozi lokaci uniformy do cache

    return location; // vrati lokaci uniformy
}
