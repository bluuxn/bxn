#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <stdbool.h>

extern GLFWwindow *_window;

void _window_framebuffer_size_callback(GLFWwindow *window, int width, int height);

void WindowInit(int width, int height, const char *title);

void WindowDestroy(void);

bool WindowRunning(void);
