#pragma once

#include "gl_resource.hpp"

namespace glt
{
    class VertexArray;
    using VertexArrayRef = base::Ref<VertexArray>;
    using VertexArrayWeakRef = base::WeakRef<VertexArray>;

    class VertexArray : public GLResource
    {
    public:
        static VertexArrayRef create()
        {
            GLuint id;
            glGenVertexArrays(1, &id);
            if (id == 0)
                std::runtime_error("Failed to create VertexArray object");

            auto vertex_array = VertexArrayRef(new VertexArray());
            vertex_array->m_id = id;
            return vertex_array;
        }

        static void unbind() { glBindVertexArray(0); }

    private:
        GLuint m_id = 0;

    protected:
        VertexArray() = default;

    public:
        ~VertexArray() override { glDeleteVertexArrays(1, &m_id); }

    public:
        GLuint get_id() const { return m_id; }
        base::Enum get_resource_type() const override { return static_cast<base::Enum>(ResourceType::VertexArray); }

    public:
        void bind() { glBindVertexArray(m_id); }
    };

} // namespace glt
