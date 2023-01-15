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

#include "libre/opengl.h"

#include <GLFW/glfw3.h>
#include <string.h>
#include <stddef.h>

#ifdef _WIN32
#include <Windows.h>
#include <GL/GL.h>
#else
#include <GL/gl.h>
#endif

libre_opengl_buffer_object_t libre_opengl_buffer_object(libre_window_t window, GLenum target)
{
    glfwMakeContextCurrent(window.window);

    libre_opengl_buffer_object_t buffer_object = {0};
    buffer_object.window = window;
    buffer_object.target = target;

    glGenBuffers(1, &buffer_object.id);

    return buffer_object;
}

void libre_opengl_buffer_object_bind(libre_opengl_buffer_object_t buffer_object)
{
    glfwMakeContextCurrent(buffer_object.window.window);
    glBindBuffer(buffer_object.target, buffer_object.id);
}

int libre_opengl_buffer_object_update(libre_opengl_buffer_object_t buffer_object, void *data, GLsizeiptr data_size)
{
    if (!data || data_size == 0)
        return -1;
    buffer_object.size = data_size;

    libre_opengl_buffer_object_bind(buffer_object);
    glBufferData(buffer_object.target, data_size, data, GL_STREAM_DRAW);

    return 0;
}

void libre_opengl_buffer_object_destroy(libre_opengl_buffer_object_t buffer_object)
{
    glfwMakeContextCurrent(buffer_object.window.window);

    glBindBuffer(buffer_object.target, 0);
    glDeleteBuffers(1, &buffer_object.id);
}

libre_opengl_vao_t libre_opengl_vao(libre_window_t window)
{
    libre_opengl_vao_t vao = {0};
    vao.window = window;

    glGenVertexArrays(1, &vao.id);

    return vao;
}

void libre_opengl_vao_bind(libre_opengl_vao_t vao)
{
    glBindVertexArray(vao.id);
}

void libre_opengl_vao_pointer(libre_opengl_vao_t vao, GLuint index, GLint size, GLenum type, GLsizei stride, GLint offset)
{
    libre_opengl_vao_bind(vao);
    glEnableVertexAttribArray(index);

    glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void *)(size_t)offset);
}

void libre_opengl_vao_destroy(libre_opengl_vao_t vao)
{
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &vao.id);
}

int libre_opengl_shader(libre_window_t window, char *vertex_shader, char *fragment_shader, libre_opengl_shader_t *shader)
{
    if (!shader)
        return -1;
    memset(shader, 0, sizeof(*shader));

    shader->window = window;

    glfwMakeContextCurrent(shader->window.window);

    GLuint vertex_id = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_id = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertex_id, 1, (const char **)&vertex_shader, NULL);
    glShaderSource(fragment_id, 1, (const char **)&fragment_shader, NULL);

    glCompileShader(vertex_id);
    glCompileShader(fragment_id);

    GLint result;
    glGetShaderiv(vertex_id, GL_COMPILE_STATUS, &result);
    if (result != GL_TRUE)
    {
        glDeleteShader(vertex_id);
        glDeleteShader(fragment_id);
        return -1;
    }

    glGetShaderiv(fragment_id, GL_COMPILE_STATUS, &result);
    if (result != GL_TRUE)
    {
        glDeleteShader(vertex_id);
        glDeleteShader(fragment_id);
        return -1;
    }

    shader->id = glCreateProgram();
    glAttachShader(shader->id, vertex_id);
    glAttachShader(shader->id, fragment_id);
    glLinkProgram(shader->id);

    glGetProgramiv(shader->id, GL_LINK_STATUS, &result);
    if (result != GL_TRUE)
    {
        glDeleteShader(vertex_id);
        glDeleteShader(fragment_id);
        return -1;
    }

    glDeleteShader(vertex_id);
    glDeleteShader(fragment_id);
    return 0;
}

void libre_opengl_shader_use(libre_opengl_shader_t shader)
{
    glfwMakeContextCurrent(shader.window.window);
    glUseProgram(shader.id);
}

GLint libre_opengl_shader_attrib_location(libre_opengl_shader_t shader, char *name)
{
    libre_opengl_shader_use(shader);
    return glGetAttribLocation(shader.id, name);
}

void libre_opengl_shader_destroy(libre_opengl_shader_t shader)
{
    glDeleteProgram(shader.id);
}

libre_opengl_texture_t libre_opengl_texture(libre_window_t window, GLsizei width, GLsizei height, uint8_t *data, GLint wrap, GLint filter)
{
    libre_opengl_texture_t texture = {0};
    texture.window = window;

    glfwMakeContextCurrent(texture.window.window);

    glCreateTextures(GL_TEXTURE_2D, 1, &texture.id);
    libre_opengl_texture_bind(texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    return texture;
}

void libre_opengl_texture_bind(libre_opengl_texture_t texture)
{
    glBindTexture(GL_TEXTURE_2D, texture.id);
}

void libre_opengl_texture_destroy(libre_opengl_texture_t texture)
{
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(1, &texture.id);
}
