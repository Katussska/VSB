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
            -0.5f, 0.5f,
            // druhy ctverec
            0.5f, 0.5f,
            1.5f, 0.5f,
            1.5f, 1.5f,
            0.5f, 1.5f,
            // trojuhelník
            -0.8f, -0.8f,
            -0.8f, 0.8f,
            -0.6f, 0.3f};

        // indexy vrcholu pro vykresleni trojuhelniku
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0,
            // druhy ctverec
            4, 5, 6,
            6, 7, 4,
            // trojuhelník
            8, 9, 10};

        VertexArray va;                                     // vytvoreni vertex array objektu
        VertexBuffer vb(positions, 11 * 2 * sizeof(float)); // naplneni bufferu pozicemi

        VertexBufferLayout layout;
        layout.Push(GL_FLOAT, 2); // specifikace layoutu bufferu (2 floaty na vrchol)
        va.AddBuffer(vb, layout); // pridani bufferu do vertex array

        IndexBuffer ib(indices, 15); // vytvoreni indexoveho bufferu

        Shader shader1("../res/shaders/Basic.shader");  // nacteni shaderu1
        Shader shader2("../res/shaders/Basic2.shader"); // nacteni shaderu2
        Shader shader3("../res/shaders/Basic3.shader"); // nacteni shaderu3

        shader1.Bind(); // aktivace shaderu1
        shader2.Bind(); // aktivace shaderu2
        shader3.Bind(); // aktivace shaderu3

        va.Unbind(); // unbindovani vsech objektu
        vb.Unbind();
        ib.Unbind();
        shader1.Unbind();
        shader2.Unbind();
        shader3.Unbind();

        Renderer renderer; // renderer pro vykreslovani

        float r = 0.0f;          // inicializace barvy
        float increment = 0.01f; // rychlost zmeny barvy

        // hlavni renderovaci smycka
        while (!glfwWindowShouldClose(window))
        {
            renderer.Clear(); // cisteni obrazovky

            shader1.Bind(); // aktivace prvniho shaderu
            shader2.Bind(); // aktivace druheho shaderu
            shader3.Bind(); // aktivace tretiho shaderu

            // vykresleni prvniho ctverce
            shader1.SetUniform4f("u_Color", r, 0.5f, 0.5f, 1.0f); // nastaveni barvy
            renderer.Draw(va, ib, shader1, 0, 6);                 // vykresleni prvniho ctverce (6 indexu)

            // vykresleni druheho ctverce
            shader2.SetUniform4f("u_Color", r, 0.1f, 0.5f, 1.0f); // nastaveni barvy
            renderer.Draw(va, ib, shader2, 6, 6);                 // vykresleni druheho ctverce (6 indexu)

            // vykresleni trojuhelniku
            shader3.SetUniform4f("u_Color", r, 0.5f, 0.1f, 1.0f); // nastaveni barvy
            renderer.Draw(va, ib, shader3, 12, 3);                // vykresleni trojuhelniku (3 indexy)

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
