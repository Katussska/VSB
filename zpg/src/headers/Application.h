#ifndef APPLICATION_H
#define APPLICATION_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <vector>

#include "ShaderProgram.h"
#include "ShaderLoader.h"
#include "ErrorHandler.h"
#include "Model.h"

// třída application spravující okno a běh aplikace
class Application
{
private:
    GLFWwindow *window; // ukazatel na okno

public:
    Application();  // konstruktor
    ~Application(); // destruktor

    void run(Application app, std::vector<ShaderProgram> &programs, std::vector<Model> &models); // hlavní smyčka aplikace
    bool shouldClose() const;                                                                    // kontrola, zda se má okno zavřít
    void swapBuffers() const;                                                                    // výměna bufferů
    void pollEvents() const;                                                                     // zpracování událostí
};

#endif // APPLICATION_H
