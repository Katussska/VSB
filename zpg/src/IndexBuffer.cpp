#include "headers/IndexBuffer.h"
#include "headers/Renderer.h"

// konstruktor pro vytvoreni indexoveho bufferu
IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count)
    : m_Count(count) // inicializace poctu indexu
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint)); // kontrola, zda velikost unsigned int odpovida GLuint

    GLCall(glGenBuffers(1, &m_RendererID));                                                            // generovani bufferu a ulozeni jeho id
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));                                       // bindovani bufferu jako element array buffer
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW)); // naplneni bufferu daty
}

// destruktor pro smazani bufferu
IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID)); // smazani bufferu podle id
}

// metoda pro bindovani bufferu
void IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); // bindovani bufferu
}

// metoda pro unbindovani bufferu
void IndexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); // unbindovani bufferu
}
