#pragma once

// trida pro spravu vertex bufferu
class VertexBuffer
{
private:
    unsigned int m_RendererID; // identifikator vertex bufferu pro renderer

public:
    // konstruktor pro inicializaci vertex bufferu s daty a velikosti
    VertexBuffer(const void *data, unsigned int size);

    // destruktor pro uvolneni vertex bufferu
    ~VertexBuffer();

    // metoda pro aktivaci vertex bufferu
    void Bind() const;

    // metoda pro deaktivaci vertex bufferu
    void Unbind() const;
};
