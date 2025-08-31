#pragma once

#include <glad/gl.h>

typedef struct Texture {
    GLuint id;
    int width;
    int height;
    unsigned char *data;
} Texture;

Texture TextureLoad(const char *file_path);

Texture TextureLoadPro(unsigned char *data, int width, int height);
