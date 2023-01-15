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

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

#include "window.h"

#ifdef _WIN32
#include <Windows.h>
#include <GL/GL.h>
#else
#include <GL/gl.h>
#endif

typedef struct libre_opengl_buffer_object
{
    libre_window_t window;
    GLenum target;
    GLuint id;
    GLsizeiptr size;
} libre_opengl_buffer_object_t;

typedef struct libre_opengl_vao
{
    libre_window_t window;
    GLuint id;
} libre_opengl_vao_t;

typedef struct libre_opengl_shader
{
    libre_window_t window;
    GLuint id;
} libre_opengl_shader_t;

typedef struct libre_opengl_texture
{
    libre_window_t window;
    GLuint id;
} libre_opengl_texture_t;

libre_opengl_buffer_object_t libre_opengl_buffer_object(libre_window_t window, GLenum target);
void libre_opengl_buffer_object_bind(libre_opengl_buffer_object_t buffer_object);
int libre_opengl_buffer_object_update(libre_opengl_buffer_object_t buffer_object, void *data, GLsizeiptr data_size);
void libre_opengl_buffer_object_destroy(libre_opengl_buffer_object_t buffer_object);

libre_opengl_vao_t libre_opengl_vao(libre_window_t window);
void libre_opengl_vao_bind(libre_opengl_vao_t vao);
void libre_opengl_vao_pointer(libre_opengl_vao_t vao, GLuint index, GLint size, GLenum type, GLsizei stride, GLint offset);
void libre_opengl_vao_destroy(libre_opengl_vao_t vao);

int libre_opengl_shader(libre_window_t window, char *vertex_shader, char *fragment_shader, libre_opengl_shader_t *shader);
void libre_opengl_shader_use(libre_opengl_shader_t shader);
GLint libre_opengl_shader_attrib_location(libre_opengl_shader_t shader, char *name);
void libre_opengl_shader_destroy(libre_opengl_shader_t shader);

libre_opengl_texture_t libre_opengl_texture(libre_window_t window, GLsizei width, GLsizei height, uint8_t *data, GLint wrap, GLint filter);
void libre_opengl_texture_bind(libre_opengl_texture_t texture);
void libre_opengl_texture_destroy(libre_opengl_texture_t texture);

#ifdef __cplusplus
}
#endif
