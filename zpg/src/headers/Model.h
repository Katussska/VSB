#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>

// třída model pro reprezentaci 3D modelu
class Model
{
private:
    GLuint VAO;         // id vertex array objektu
    GLuint VBO;         // id vertex buffer objektu
    float points[9] = { // vrcholy modelu
        -0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f};

public:
    Model();      // konstruktor
    void setup(); // nastavení modelu
    void draw();  // vykreslení modelu
};

#endif // MODEL_H