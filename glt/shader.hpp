#pragma once

#include <string>
#include "gl_resource.hpp"

namespace glt
{
    class Shader;
    using ShaderRef = base::Ref<Shader>;
    using ShaderWeakRef = base::WeakRef<Shader>;

    /// @brief 着色器对象
    class Shader : public GLResource
    {
    public:
        /// @brief 着色器类型
        enum class ShaderType : GLenum
        {
            Vertex = GL_VERTEX_SHADER,
            Fragment = GL_FRAGMENT_SHADER,
        };

        static ShaderRef create(ShaderType type)
        {
            GLuint id = glCreateShader(static_cast<GLenum>(type));
            if (id == 0)
                throw std::runtime_error(base::to_string(
                    "Failed to create Shader, type: ",
                    static_cast<base::Enum>(type)));

            auto shader = ShaderRef(new Shader());
            shader->m_id = id;
            shader->m_type = type;
            return shader;
        }

    private:
        GLuint m_id = 0;
        ShaderType m_type;

    protected:
        Shader() = default;

    public:
        ~Shader() override { glDeleteShader(m_id); }

    public:
        GLuint get_id() const { return m_id; }
        ShaderType get_type() const { return m_type; }
        base::Enum get_resource_type() const override { return static_cast<base::Enum>(ResourceType::Shader); }

    public:
        void shader_source(const std::string &source)
        {
            const char *source_ptr = source.data();
            glShaderSource(m_id, 1, &source_ptr, nullptr);
        }

        void compile_shader()
        {
            glCompileShader(m_id);

            GLint length = 0;
            glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &length);
            if (length == 0)
                return;

            std::string info_log;
            info_log.resize(length);
            glGetShaderInfoLog(m_id, length, nullptr, info_log.data());
            throw std::runtime_error(base::to_string(
                "Failed to compile shader, info log:\n",
                info_log));
        }
    };

} // namespace glt
