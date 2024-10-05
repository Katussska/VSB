#include "headers/Application.h"

// konstruktor, inicializuje glfw a vytvoří okno
Application::Application()
    : window(nullptr)
{
    // nastavení callbacku pro chyby glfw
    glfwSetErrorCallback(ErrorHandler::errorCallbackGLFW);

    // inicializace glfw
    if (!glfwInit())
    {
        std::cerr << "ERROR: could not start GLFW3\n";
        exit(EXIT_FAILURE);
    }

    // vytvoření okna
    window = glfwCreateWindow(800, 600, "Shader Program", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // nastavení kontextu pro opengl
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE; // povolení experimentálních funkcí
    glewInit();                 // inicializace glew
    glViewport(0, 0, 800, 600); // nastavení viewportu
}

// destruktor, uvolňuje prostředky
Application::~Application()
{
    if (window)
        glfwDestroyWindow(window); // zničení okna

    glfwTerminate(); // uvolnění glfw
}

// hlavní smyčka aplikace
void Application::run(Application app, std::vector<ShaderProgram> &programs, std::vector<Model> &models)
{
    // získání informací o verzi opengl a glew
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);

    // hlavní smyčka aplikace
    while (!app.shouldClose())
    {
        // vymazání barevného a hloubkového bufferu
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // kreslení všech shader programů
        for (size_t i = 0; i < programs.size(); ++i)
        {
            programs[i].useProgram(); // použití shader programu

            // kreslení všech modelů
            for (auto &model : models)
                model.draw(); // kreslení modelu
        }

        app.swapBuffers(); // výměna bufferů
        app.pollEvents();  // zpracování událostí
    }
}

// kontrola, zda se má okno zavřít
bool Application::shouldClose() const
{
    return glfwWindowShouldClose(window);
}

// výměna bufferů okna
void Application::swapBuffers() const
{
    glfwSwapBuffers(window);
}

// zpracování událostí
void Application::pollEvents() const
{
    glfwPollEvents();
}