/*
BSD 2-Clause License

Copyright (c) 2023, Caleb Heydon
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <GL/glew.h>

#include <libre/libre.h>
#include <stdio.h>
#include <libre/window.h>
#include <GLFW/glfw3.h>
#include <libre/opengl.h>
#include <stdint.h>

#ifdef _WIN32
#include <Windows.h>
#include <GL/GL.h>
#else
#include <GL/gl.h>
#endif

int main(int argc, char **argv)
{
    libre_version_t version = libre_version();
    printf("libre version: %d.%d.%d\n", version.major, version.minor, version.patch);

    if (libre_window_init())
    {
        printf("failed to initialize glfw\n");
        return -1;
    }

    libre_window_t window;
    if (libre_window_create(&window, 852, 480, "test_opengl", false))
    {
        printf("failed to create window\n");
        return -1;
    }

    libre_window_center(window);
    libre_window_show(window);

    glfwMakeContextCurrent(window.window);

    if (glewInit() != GLEW_OK)
    {
        printf("failed to initialize glew\n");
        return -1;
    }

    glClearColor(0, 0, 0, 1.0f);

    float vbo_data[2 * 4];

    vbo_data[0] = -0.5f;
    vbo_data[1] = 0.5f;

    vbo_data[2] = -0.5f;
    vbo_data[3] = -0.5f;

    vbo_data[4] = 0.5f;
    vbo_data[5] = -0.5f;

    vbo_data[6] = 0.5f;
    vbo_data[7] = 0.5f;

    uint32_t ibo_data[6];
    ibo_data[0] = 0;
    ibo_data[1] = 1;
    ibo_data[2] = 2;
    ibo_data[3] = 0;
    ibo_data[4] = 2;
    ibo_data[5] = 3;

    libre_opengl_buffer_object_t vbo = libre_opengl_buffer_object(window, GL_ARRAY_BUFFER);
    libre_opengl_buffer_object_update(vbo, vbo_data, sizeof(vbo_data));

    libre_opengl_buffer_object_t ibo = libre_opengl_buffer_object(window, GL_ELEMENT_ARRAY_BUFFER);
    libre_opengl_buffer_object_update(ibo, ibo_data, sizeof(ibo_data));

    libre_opengl_shader_t shader;
    if (libre_opengl_shader(window, "#version 330 core\nin vec2 position;\nvoid main() {\ngl_Position = vec4(position, 0, 1.0);\n}\n", "#version 330 core\nout vec4 frag_color;\nvoid main() {\nfrag_color = vec4(0, 1.0, 0, 1.0);\n}\n", &shader))
    {
        printf("failed to build shader\n");
        return -1;
    }

    libre_opengl_vao_t vao = libre_opengl_vao(window);
    libre_opengl_vao_pointer(vao, libre_opengl_shader_attrib_location(shader, "position"), 2, GL_FLOAT, sizeof(float) * 2, 0);

    while (!libre_window_should_close(window))
    {
        glfwMakeContextCurrent(window.window);
        glfwSwapInterval(1);

        int width, height;
        glfwGetWindowSize(window.window, &width, &height);
        glViewport(0, 0, width, height);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        libre_opengl_shader_use(shader);
        libre_opengl_buffer_object_bind(vbo);
        libre_opengl_buffer_object_bind(ibo);
        libre_opengl_vao_bind(vao);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

        libre_window_swap_buffers(window);
        libre_window_poll_events();
    }

    libre_opengl_vao_destroy(vao);
    libre_opengl_shader_destroy(shader);
    libre_opengl_buffer_object_destroy(ibo);
    libre_opengl_buffer_object_destroy(vbo);
    libre_window_destroy(window);

    libre_window_terminate();

    return 0;
}
