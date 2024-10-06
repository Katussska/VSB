#include "headers/VertexBuffer.h"
#include "headers/VertexBufferLayout.h"
#include "headers/Renderer.h"

// konstruktor inicializuje VertexBuffer, vytvori a nabinduje buffer a nahraje data do graficke pameti
VertexBuffer::VertexBuffer(const void *data, unsigned int size)
{
    GLCall(glGenBuffers(1, &m_RendererID));                            // generuje 1 buffer a uklada jeho id do m_RendererID
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));               // binduje buffer typu GL_ARRAY_BUFFER
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW)); // nahrava data do bufferu a specifikuje, ze se nebudou casto menit
}

// destruktor uvolnuje graficky buffer pri ruseni objektu
VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID)); // maze buffer na zaklade jeho id
}

// funkce binduje buffer, aby ho bylo mozne pouzit
void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); // znovu binduje buffer pro pozdejsi operace
}

// funkce unbinduje buffer, kdyz ho uz neni treba pouzivat
void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); // unbinduje buffer nastavenim 0
}
