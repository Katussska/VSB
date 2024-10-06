#include "headers/Renderer.h"

#include <iostream>

// funkce cisti vsechny OpenGL chyby, dokud nejake existuji
void GLClearError()
{
    while (glGetError() != GL_NO_ERROR) // dokud existuje chyba
        ;                               // ignoruje hodnotu, pouze cisti
}

// funkce loguje OpenGL chyby, pokud k nejake dojde a vraci false
bool GLLogCall(const char *function, const char *file, int line)
{
    while (GLenum error = glGetError()) // kontroluje, zda existuje OpenGL chyba
    {
        // vypise chybu do cerr s informacemi o funkci, souboru a radku
        std::cerr << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
        return false; // vrati false, pokud se chyba objevi
    }
    return true; // pokud chyby nejsou, vrati true
}

// funkce cisti obrazovku pomoci OpenGL volani glClear
void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT)); // cisti barevny buffer
}

// funkce vykresluje objekt na obrazovku
void Renderer::Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader, unsigned int offset, unsigned int count) const
{
    shader.Bind(); // aktivuje shaderovy program
    va.Bind();     // binduje vertex array objekt
    ib.Bind();     // binduje index buffer

    // vykresluje trojuhelniky na zaklade indexu v ib (index buffer) s offsetem a poctem indexu
    GLCall(glDrawElementsBaseVertex(GL_TRIANGLES, count, GL_UNSIGNED_INT, (const void *)(offset * sizeof(unsigned int)), 0));
}
