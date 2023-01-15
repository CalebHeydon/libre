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

#include <GLFW/glfw3.h>
#include <stdbool.h>

typedef struct libre_window
{
    GLFWwindow *window;
} libre_window_t;

int libre_window_init(void);
void libre_window_terminate(void);
void libre_window_poll_events(void);
int libre_window_create(libre_window_t *window, int width, int height, char *title, bool vulkan);
void libre_window_show(libre_window_t window);
void libre_window_hide(libre_window_t window);
void libre_window_fullsreen(libre_window_t window, bool fullscreen);
bool libre_window_should_close(libre_window_t window);
void libre_window_destroy(libre_window_t window);
void libre_window_swap_buffers(libre_window_t window);
void libre_window_center(libre_window_t window);

#ifdef __cplusplus
}
#endif
