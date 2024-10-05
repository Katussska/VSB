#include "headers/Model.h"

// konstruktor třídy model, inicializuje VAO a VBO na 0
Model::Model() : VAO(0), VBO(0) {}

// nastavení vertex buffer a vertex array
void Model::setup()
{
    glGenBuffers(1, &VBO);                                                 // vygenerování vertex bufferu
    glBindBuffer(GL_ARRAY_BUFFER, VBO);                                    // navázání vertex bufferu
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW); // naplnění vertex bufferu

    glGenVertexArrays(1, &VAO);                               // vygenerování vertex array
    glBindVertexArray(VAO);                                   // navázání vertex array
    glEnableVertexAttribArray(0);                             // povolení atributu 0
    glBindBuffer(GL_ARRAY_BUFFER, VBO);                       // navázání vertex bufferu
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL); // nastavení atributu vertexu
}

// vykreslení modelu
void Model::draw()
{
    glBindVertexArray(VAO);           // navázání vertex array
    glDrawArrays(GL_TRIANGLES, 0, 3); // vykreslení modelu jako trojúhelníků
}
