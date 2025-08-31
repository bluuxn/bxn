#include "platform.h"

#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <stdio.h>

GLFWwindow *_window = NULL;

void _window_framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void WindowInit(int width, int height, const char *title) {
    if (!glfwInit()) {
        printf("[!GLFW] Failed to initialize GLFW!\n");
        return;
    }
    int glfwMajor, glfwMinor, glfwPatch;
    glfwGetVersion(&glfwMajor, &glfwMinor, &glfwPatch);
    printf("[GLFW] Initialized GLFW %d.%d.%d!\n", glfwMajor, glfwMinor, glfwPatch);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (_window == NULL) {
        printf("[!GLFW] Failed to create GLFW window!\n");
        glfwTerminate();
        return;
    }
    printf("[GLFW] Created GLFW window!\n");

    glfwMakeContextCurrent(_window);

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        printf("[!GLAD] Failed to load OpenGL!\n");
        glfwTerminate();
        glfwDestroyWindow(_window);
        return;
    }
    printf("[GLAD] Loaded OpenGL version %d.%d!\n",
            GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

    glfwSetFramebufferSizeCallback(_window, _window_framebuffer_size_callback);
}

void WindowDestroy(void) {
    glfwMakeContextCurrent(NULL);
    printf("[GLFW] Destroying window!\n");
    glfwDestroyWindow(_window);
    printf("[GLFW] Terminating GLFW!\n");
    glfwTerminate();
}

bool WindowRunning(void) {
    return !glfwWindowShouldClose(_window);
}
