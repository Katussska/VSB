#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <GL/glew.h>
#include "Shader.h"

// třída shaderprogram pro správu shader programu
class ShaderProgram
{
private:
    GLuint programID; // id shader programu
public:
    ShaderProgram(VertexShader &vertexShader, FragmentShader &fragmentShader); // konstruktor
    void useProgram();                                                         // použití shader programu
};

#endif // SHADER_PROGRAM_H