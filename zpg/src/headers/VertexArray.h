#pragma once

#include "VertexBuffer.h"

// třída pro správu vertex array
class VertexBufferLayout; // předběžná deklarace třídy VertexBufferLayout

class VertexArray
{
private:
    unsigned int m_RendererID; // identifikátor vertex array pro renderer

public:
    // konstruktor pro inicializaci vertex array
    VertexArray(/* args */);

    // destruktor pro uvolnění vertex array
    ~VertexArray();

    // metoda pro přidání vertex bufferu a jeho layoutu do vertex array
    void AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout);

    // metoda pro aktivaci vertex array
    void Bind() const;

    // metoda pro deaktivaci vertex array
    void Unbind() const;
};
