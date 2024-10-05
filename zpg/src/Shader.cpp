#include "headers/Shader.h"
#include <iostream>

// konstruktor třídy shader, vytváří shader
Shader::Shader(const std::string &source)
{
    // vytvoření shaderu
    shaderID = glCreateShader(GL_VERTEX_SHADER); // změní se na GL_FRAGMENT_SHADER v odvozených třídách
    const char *shaderSource = source.c_str();
    glShaderSource(shaderID, 1, &shaderSource, NULL);
    compileShader(); // kompilace shaderu
}

// destruktor třídy shader
Shader::~Shader()
{
    glDeleteShader(shaderID); // odstranění shaderu
}

// získání id shaderu
GLuint Shader::getID() const
{
    return shaderID;
}

// kompilace shaderu
void Shader::compileShader()
{
    glCompileShader(shaderID); // kompilace shaderu
    GLint status;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status); // získání stavu kompilace
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength); // získání délky logu chyb
        std::string infoLog(infoLogLength, ' ');
        glGetShaderInfoLog(shaderID, infoLogLength, NULL, &infoLog[0]);     // získání logu chyb
        std::cerr << "Shader compilation failed: " << infoLog << std::endl; // výpis chybového logu
    }
}

// konstruktor třídy vertexshader
VertexShader::VertexShader(const std::string &source) : Shader(source)
{
    // nastavení typu shaderu na vertex shader
    shaderID = glCreateShader(GL_VERTEX_SHADER);
}

// konstruktor třídy fragmentshader
FragmentShader::FragmentShader(const std::string &source) : Shader(source)
{
    // nastavení typu shaderu na fragment shader
    shaderID = glCreateShader(GL_FRAGMENT_SHADER);
}