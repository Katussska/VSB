#include "headers/ShaderProgram.h"
#include <iostream>

// konstruktor třídy shaderprogram, vytváří shader program a připojuje shadery
ShaderProgram::ShaderProgram(VertexShader &vertexShader, FragmentShader &fragmentShader)
{
    programID = glCreateProgram();                     // vytvoření shader programu
    glAttachShader(programID, vertexShader.getID());   // připojení vertex shaderu
    glAttachShader(programID, fragmentShader.getID()); // připojení fragment shaderu
    glLinkProgram(programID);                          // prolinkování shader programu

    GLint status;
    glGetProgramiv(programID, GL_LINK_STATUS, &status); // získání stavu prolinkování
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength); // získání délky logu chyb
        std::string infoLog(infoLogLength, ' ');
        glGetProgramInfoLog(programID, infoLogLength, NULL, &infoLog[0]);       // získání logu chyb
        std::cerr << "Shader program linking failed: " << infoLog << std::endl; // výpis chybového logu
    }
}

// použití shader programu
void ShaderProgram::useProgram()
{
    glUseProgram(programID); // aktivace shader programu
}
