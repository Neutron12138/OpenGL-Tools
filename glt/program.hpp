#pragma once

#include "shader.hpp"

namespace glt
{
    class Program;
    using ProgramRef = base::Ref<Program>;
    using ProgramWeakRef = base::WeakRef<Program>;

    /// @brief 着色器程序对象
    class Program : public GLResource
    {
    public:
        static ProgramRef create()
        {
            GLuint id = glCreateProgram();
            if (id == 0)
                throw std::runtime_error("Failed to create Program");

            auto program = ProgramRef(new Program());
            program->m_id = id;
            return program;
        }

    private:
        GLuint m_id = 0;

    protected:
        Program() = default;

    public:
        ~Program() override { glDeleteProgram(m_id); }

    public:
        GLuint get_id() const { return m_id; }
        base::Enum get_resource_type() const { return static_cast<base::Enum>(ResourceType::Program); }

    public:
        void use_program() { glUseProgram(m_id); }

        void attach_shader(const ShaderRef &shader)
        {
            if (!shader)
                throw std::runtime_error("Cannot attach an invalid shader");

            glAttachShader(m_id, shader->get_id());
        }

        void link_program()
        {
            glLinkProgram(m_id);

            GLint length;
            glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &length);
            if (length == 0)
                return;

            std::string info_log;
            info_log.resize(length);
            glGetProgramInfoLog(m_id, length, nullptr, info_log.data());
            throw std::runtime_error(base::to_string(
                "Failed to link program, info log:\n",
                info_log));
        }
    };

} // namespace glt
