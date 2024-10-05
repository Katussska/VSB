#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <iostream>

class ErrorHandler
{
public:
    // Static method for GLFW error callback
    static void errorCallbackGLFW(int error, const char *description)
    {
        std::cerr << "GLFW Error [" << error << "]: " << description << std::endl;
    }
};

#endif // ERROR_HANDLER_H
