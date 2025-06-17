#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <base/base.hpp>

namespace glt
{
    void glfw_error_callback(int error_code, const char *description)
    {
        std::cout << "glfw error callback, error_code: " << error_code
                  << ", description: \"" << description << "\"" << std::endl;
    }

    void init_glfw(int major, int minor, int profile = GLFW_OPENGL_CORE_PROFILE)
    {
        glfwSetErrorCallback(glfw_error_callback);

        int error = glfwInit();
        if (error != GLFW_TRUE)
            throw std::runtime_error("Failed to initialize GLFW");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, profile);
    }

    void init_glfw()
    {
        init_glfw(3, 3);
    }

    void term_glfw()
    {
        glfwTerminate();
    }

    GLFWwindow *create_glfw_window(int width, int height, const char *title = "",
                                   GLFWmonitor *monitor = nullptr, GLFWwindow *share = nullptr)
    {
        GLFWwindow *window = glfwCreateWindow(width, height, title, monitor, share);
        if (!window)
            throw std::runtime_error(base::to_string(
                "Failed to create GLFW window with width: ", width,
                ", height: ", height,
                ", title: \"", title,
                "\", monitor: ", monitor,
                ", share: ", share));

        return window;
    }

} // namespace glt
