#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include <GL/glew.h>

// makro pro kontrolu zda podminka plati jinak spusti trap zastaveni programu
#define ASSERT(x) \
    if (!(x))     \
        __builtin_trap();

// makro pro volani OpenGL funkci s kontrolou chyb
#define GLCall(x)                                                         \
    GLClearError();                           /* vycisteni OpenGL chyb */ \
    x;                                        /* volani OpenGL funkce */  \
    ASSERT(GLLogCall(#x, __FILE__, __LINE__)) /* kontrola zda probehla bez chyb */

// funkce pro vycisteni OpenGL chyb
void GLClearError();

// funkce pro logovani OpenGL chyb vraci false pokud doslo k chybe
bool GLLogCall(const char *function, const char *file, int line);

// trida Renderer pro vykreslovani objektu
class Renderer
{
public:
    // metoda pro vycisteni obrazovky
    void Clear() const;

    // metoda pro vykresleni objektu vertex array index buffer shader
    void Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const;
};
