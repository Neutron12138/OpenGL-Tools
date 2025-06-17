#pragma once

#include <vector>
#include "gl_resource.hpp"

namespace glt
{
    class Buffer;
    using BufferRef = base::Ref<Buffer>;
    using BufferWeakRef = base::WeakRef<Buffer>;

    /// @brief 缓冲区对象
    class Buffer : public GLResource
    {
    public:
        /// @brief 缓冲区类型
        enum class BufferType : GLenum
        {
            Array = GL_ARRAY_BUFFER,
            ElementArray = GL_ELEMENT_ARRAY_BUFFER,
        };

        static BufferRef create(BufferType type)
        {
            GLuint id = 0;
            glGenBuffers(1, &id);
            if (id == 0)
                throw std::runtime_error("Failed to generate buffer ID for Buffer object");

            auto buffer = BufferRef(new Buffer());
            buffer->m_id = id;
            buffer->m_type = type;
            return buffer;
        }

    private:
        GLuint m_id = 0;
        BufferType m_type;

    protected:
        Buffer() = default;

    public:
        ~Buffer() override { glDeleteBuffers(1, &m_id); }

    public:
        GLuint get_id() const { return m_id; }
        BufferType get_type() const { return m_type; }
        base::Enum get_resource_type() const override { return static_cast<base::Enum>(ResourceType::Buffer); }

    public:
        void bind() { glBindBuffer(static_cast<GLenum>(m_type), m_id); }
        void unbind() { glBindBuffer(static_cast<GLenum>(m_type), 0); }

        void buffer_data(GLsizeiptr size, const void *data, GLenum usage = GL_STATIC_DRAW)
        {
            glBufferData(static_cast<GLenum>(m_type), size, data, usage);
        }

        template <typename T>
        void buffer_data(const std::vector<T> &vertices, GLenum usage = GL_STATIC_DRAW)
        {
            buffer_data(vertices.size() * sizeof(T), vertices.data(), usage);
        }

        void vertex_attrib_pointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer = nullptr)
        {
            glVertexAttribPointer(index, size, type, normalized, stride, pointer);
        }

        void vertex_attrib_pointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer = nullptr)
        {
            glVertexAttribPointer(index, size, type, GL_FALSE, stride, pointer);
        }

        void enable_vertex_attrib_array(GLuint index)
        {
            glEnableVertexAttribArray(index);
        }
    };

} // namespace glt
