#include "headers/Application.h"

int main()
{
    Application app; // vytvoření instance aplikace

    // načtení shaderů ze souborů
    std::string vertexShaderSource = ShaderLoader::loadShaderFromFile("../shaders/vertex_shader.glsl");     // načtení vertex shaderu
    std::string fragmentShaderSource = ShaderLoader::loadShaderFromFile("../shaders/fragment_shader.glsl"); // načtení fragment shaderu

    // vytvoření shaderů
    VertexShader vertexShader(vertexShaderSource);       // inicializace vertex shaderu
    FragmentShader fragmentShader(fragmentShaderSource); // inicializace fragment shaderu

    // vytvoření shader programu
    ShaderProgram shaderProgram(vertexShader, fragmentShader); // spojení shaderů do shader programu

    // setup modelu
    Model model;   // vytvoření instance modelu
    model.setup(); // inicializace modelu

    // Create named variables for vectors
    std::vector<ShaderProgram> shaderPrograms{shaderProgram};
    std::vector<Model> models{model};

    // hlavní smyčka aplikace
    app.run(app, shaderPrograms, models); // spuštění aplikace

    return 0; // návratový kód
}