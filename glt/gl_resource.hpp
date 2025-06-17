#pragma once
#include <base/base.hpp>
#include "gl.hpp"

namespace glt
{
    /// @brief 基础OpenGL资源
    class GLResource : public base::Resource
    {
    public:
        /// @brief 资源类型
        enum class ResourceType : base::Enum
        {
            /// @brief 无
            None,
            /// @brief 缓冲区
            Buffer,
            /// @brief 顶点数组
            VertexArray,
            /// @brief 着色器
            Shader,
            /// @brief 着色器程序
            Program,
        };

    public:
        GLResource() = default;
        ~GLResource() override = default;
    };

} // namespace glt
