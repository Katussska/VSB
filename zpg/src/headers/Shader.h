#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

// třída shader reprezentující shader program
class Shader
{
protected:
    GLuint shaderID;      // id shaderu
    void compileShader(); // kompilace shaderu
public:
    Shader(const std::string &source); // konstruktor
    virtual ~Shader();                 // destruktor
    GLuint getID() const;              // získání id shaderu
};

// třída vertexshader dědící z třídy shader
class VertexShader : public Shader
{
public:
    VertexShader(const std::string &source); // konstruktor
};

// třída fragmentshader dědící z třídy shader
class FragmentShader : public Shader
{
public:
    FragmentShader(const std::string &source); // konstruktor
};

#endif // SHADER_H