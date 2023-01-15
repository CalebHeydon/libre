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

#include "libre/window.h"

#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <string.h>

int libre_window_init(void)
{
    return glfwInit() == GLFW_TRUE ? 0 : -1;
}

void libre_window_terminate(void)
{
    glfwTerminate();
}

void libre_window_poll_events(void)
{
    glfwPollEvents();
}

int libre_window_create(libre_window_t *window, int width, int height, char *title, bool vulkan)
{
    if (!window)
        return -1;
    memset(window, 0, sizeof(*window));

    if (vulkan)
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    else
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    }

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    window->window = glfwCreateWindow(width, height, title == NULL ? "" : title, NULL, NULL);
    if (!window->window)
        return -1;

    return 0;
}

void libre_window_show(libre_window_t window)
{
    glfwShowWindow(window.window);
}

void libre_window_hide(libre_window_t window)
{
    glfwHideWindow(window.window);
}

void libre_window_fullsreen(libre_window_t window, bool fullscreen)
{
    if (fullscreen)
    {
        GLFWmonitor *monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode *vidmode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(window.window, monitor, 0, 0, vidmode->width, vidmode->height, vidmode->refreshRate);

        return;
    }

    glfwSetWindowMonitor(window.window, NULL, 0, 0, 0, 0, 0);
}

bool libre_window_should_close(libre_window_t window)
{
    return glfwWindowShouldClose(window.window) ? true : false;
}

void libre_window_destroy(libre_window_t window)
{
    glfwDestroyWindow(window.window);
}

void libre_window_swap_buffers(libre_window_t window)
{
    glfwSwapBuffers(window.window);
}

void libre_window_center(libre_window_t window)
{
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    int xpos, ypos, width, height;
    glfwGetMonitorWorkarea(monitor, &xpos, &ypos, &width, &height);

    int windowWidth, windowHeight;
    glfwGetWindowSize(window.window, &windowWidth, &windowHeight);

    glfwSetWindowPos(window.window, xpos + width / 2 - windowWidth / 2, ypos + height / 2 - windowHeight / 2);
}
