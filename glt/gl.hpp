#pragma once

#include <iostream>
#include <GL/glew.h>
#include <base/base.hpp>

namespace glt
{
    /// @brief 初始化GLEW，如果失败则会抛出异常
    void init_glew()
    {
        GLenum error = glewInit();
        if (error == GLEW_OK)
            return;

        throw std::runtime_error(base::to_string(
            "Failed to initialize GLEW, reason: ",
            glewGetErrorString(error)));
    };

} // namespace glt
