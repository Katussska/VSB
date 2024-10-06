#pragma once

// trida IndexBuffer pro spravu indexoveho bufferu
class IndexBuffer
{
private:
    unsigned int m_RendererID; // identifikator bufferu pouzivany v OpenGL
    unsigned int m_Count;      // pocet indexu v bufferu

public:
    // konstruktor ktery vytvori indexovy buffer na zaklade zadanych dat a pocet indexu
    IndexBuffer(const unsigned int *data, unsigned int count);

    // destruktor pro uvolneni prostredku spojenych s indexovym bufferem
    ~IndexBuffer();

    // metoda pro bindovani indexoveho bufferu
    void Bind() const;

    // metoda pro unbindovani indexoveho bufferu
    void Unbind() const;

    // inline metoda pro ziskani pocet indexu
    inline unsigned int GetCount() const { return m_Count; }
};
