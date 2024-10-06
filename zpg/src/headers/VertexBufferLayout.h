#pragma once

#include <vector>

#include "Renderer.h"

// struktura pro uchovani informace o elementech vertex bufferu
struct VertexBufferElement
{
    unsigned int type;        // typ dat elementu
    unsigned int count;       // pocet dat elementu
    unsigned char normalized; // informuje zda jsou data normalizovana

    // staticka metoda pro ziskani velikosti typu dat
    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
        case GL_FLOAT:
            return sizeof(GLfloat); // vrati velikost float
        case GL_UNSIGNED_INT:
            return sizeof(GLuint); // vrati velikost unsigned int
        case GL_UNSIGNED_BYTE:
            return sizeof(GLubyte); // vrati velikost unsigned byte
        }
        ASSERT(false); // kontrola pro neplatny typ
        return 0;      // vraci 0 pokud typ neni platny
    }
};

// trida pro spravu rozlozeni vertex bufferu
class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> m_Elements; // vektor elementu bufferu
    unsigned int m_Stride;                       // celkova sirka bufferu

public:
    // konstruktor inicializuje m_Stride na 0
    VertexBufferLayout()
        : m_Stride(0) {}

    // metoda pro pridani elementu do bufferu
    void Push(unsigned int type, unsigned int count)
    {
        m_Elements.push_back({type, count, GL_FALSE});                // pridani noveho elementu
        m_Stride += count * VertexBufferElement::GetSizeOfType(type); // aktualizace sirky bufferu
    }

    // inline metoda pro ziskani elementu bufferu
    inline const std::vector<VertexBufferElement> &GetElements() const { return m_Elements; }

    // inline metoda pro ziskani sirky bufferu
    inline unsigned int GetStride() const { return m_Stride; }
};
