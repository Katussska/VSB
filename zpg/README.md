# ZPG

## Current Classes

- **Application**
  - Handles window setup, OpenGL context initialization, and input callbacks using GLFW.

- **Shader (base class)**
  - Base class for managing shader compilation and error checking.
  
- **VertexShader (inherits Shader)**
  - Manages vertex shader-specific functionality.

- **FragmentShader (inherits Shader)**
  - Manages fragment shader-specific functionality.

- **ShaderProgram**
  - Links vertex and fragment shaders to create a shader program. Has a `secureUse()` method to ensure proper use of the program.

- **Model**
  - Sets up VAO and VBO for rendering a triangle. Can be extended for more complex models.