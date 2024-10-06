#include "headers/VertexBufferLayout.h"
#include "headers/VertexArray.h"
#include "headers/Renderer.h"

// konstruktor vytvori vertex array objekt (vao) a ulozi jeho id do m_RendererID
VertexArray::VertexArray(/* args */)
{
    GLCall(glGenVertexArrays(1, &m_RendererID)); // generuje 1 vertex array a uklada jeho id
}

// destruktor smaze vertex array objekt pri ruseni instance
VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_RendererID)); // maze vertex array podle jeho id
}

// funkce pridava buffer a vertex buffer layout k vertex array objektu
void VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout)
{
    Bind();    // binduje vao, aby s nim bylo mozne pracovat
    vb.Bind(); // binduje vertex buffer, ktery se bude pripojovat

    const auto &elements = layout.GetElements(); // ziska seznam elementu layoutu

    for (unsigned int i = 0; i < elements.size(); i++) // prochazi kazdy element v layoutu
    {
        const auto &element = elements[i];    // nacte element
        unsigned int offset = 0;              // nastavi offset pro kazdy element
        GLCall(glEnableVertexAttribArray(i)); // povoluje atribut podle indexu
        GLCall(glVertexAttribPointer(i, element.count, element.type,
                                     element.normalized, layout.GetStride(), (const void *)offset));
        // nastavi ukazatel na atribut, specifikuje pocet, typ, normalizaci, krok a offset
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
        // posune offset na zaklade velikosti datoveho typu
    }
}

// funkce binduje vertex array objekt, aby mohl byt pouzivan
void VertexArray::Bind() const
{
    GLCall(glBindVertexArray(m_RendererID)); // binduje vao podle jeho id
}

// funkce unbinduje vertex array objekt, kdyz uz neni potreba
void VertexArray::Unbind() const
{
    GLCall(glBindVertexArray(0)); // unbinduje vao nastavenim 0
}
