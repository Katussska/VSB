#include "headers/Renderer.h"
#include "headers/VertexBufferLayout.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <GLFW/glfw3.h>

int main(void)
{
    GLFWwindow *window;

    // inicializace knihovny glfw
    if (!glfwInit())
        return -1;

    // nastaveni verze OpenGL na 3.3 a pouziti core profilu
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // vytvoreni okna s OpenGL kontextem
    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // nastaveni OpenGL kontextu pro okno
    glfwMakeContextCurrent(window);

    // nastaveni vymeny bufferu na kazdy frame
    glfwSwapInterval(1);

    // inicializace glew a kontrola, zda probehla uspesne
    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl; // vypis verze OpenGL
    {
        // pozice vrcholu ctverce
        float positions[] = {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.5f, 0.5f,
            -0.5f, 0.5f};

        // indexy vrcholu pro vykresleni trojuhelniku
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0};

        VertexArray va;                                    // vytvoreni vertex array objektu
        VertexBuffer vb(positions, 4 * 2 * sizeof(float)); // naplneni bufferu pozicemi

        VertexBufferLayout layout;
        layout.Push(GL_FLOAT, 2); // specifikace layoutu bufferu (2 floaty na vrchol)
        va.AddBuffer(vb, layout); // pridani bufferu do vertex array

        IndexBuffer ib(indices, 6); // vytvoreni indexoveho bufferu

        Shader shader("../res/shaders/Basic.shader"); // nacteni shaderu

        shader.Bind(); // aktivace shaderu

        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f); // nastaveni uniformy pro barvu

        va.Unbind(); // unbindovani vsech objektu
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Renderer renderer; // renderer pro vykreslovani

        float r = 0.0f;          // inicializace barvy
        float increment = 0.01f; // rychlost zmeny barvy

        // hlavni renderovaci smycka
        while (!glfwWindowShouldClose(window))
        {
            renderer.Clear(); // cisteni obrazovky

            shader.Bind();                                       // znovu aktivace shaderu
            shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f); // nastaveni barvy

            renderer.Draw(va, ib, shader); // vykresleni ctverce

            // zmena barvy v zavislosti na hodnote r
            if (r > 1.0f)
                increment = -0.01f;
            else if (r < 0.0f)
                increment = 0.01f;

            r += increment; // zmena hodnoty r

            // vymena front a back bufferu
            glfwSwapBuffers(window);

            // zpracovani udalosti
            glfwPollEvents();
        }
    }

    glfwTerminate(); // ukonceni glfw a uvolneni zdroju
    return 0;
}
