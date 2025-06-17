#include <iostream>
#define GLT_USE_GLFW
#include "../glt/glt.hpp"
#include <glm/glm.hpp>

int main()
{
    glt::init_glfw();

    GLFWwindow *window = glt::create_glfw_window(640, 480);
    glfwMakeContextCurrent(window);
    glt::init_glew();
    glViewport(0, 0, 640, 480);

    const std::vector<glm::vec2> vertices =
        {
            glm::vec2(-0.5f, -0.5f),
            glm::vec2(0.5f, -0.5f),
            glm::vec2(0.0f, 0.5f),
        };
    const std::string vs = "#version 330 core\n"
                           "layout (location = 0) in vec2 aPos;\n"
                           "void main()\n"
                           "{\n"
                           "   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
                           "}";
    const std::string fs = "#version 330 core\n"
                           "out vec4 FragColor;\n"
                           "void main()\n"
                           "{\n"
                           "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                           "}";

    glt::VertexArrayRef vao = glt::VertexArray::create();
    vao->bind();

    glt::BufferRef vbo = glt::Buffer::create(glt::Buffer::BufferType::Array);
    vbo->bind();
    vbo->buffer_data(vertices);
    vbo->vertex_attrib_pointer(0, 2, GL_FLOAT, 2 * sizeof(float));
    vbo->enable_vertex_attrib_array(0);

    glt::ShaderRef vshader = glt::Shader::create(glt::Shader::ShaderType::Vertex);
    vshader->shader_source(vs);
    vshader->compile_shader();

    glt::ShaderRef fshader = glt::Shader::create(glt::Shader::ShaderType::Fragment);
    fshader->shader_source(fs);
    fshader->compile_shader();

    glt::ProgramRef program = glt::Program::create();
    program->attach_shader(vshader);
    program->attach_shader(fshader);
    program->link_program();
    program->use_program();

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glt::term_glfw();

    return 0;
}
