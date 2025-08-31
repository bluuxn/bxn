#include "texture.h"

#include <stdio.h>

#include <glad/gl.h>

#include "stb_image.h"

Texture TextureLoad(const char *file_path) {
    printf("[Texture] Creating new texture for %s!\n", file_path);
    int width, height, nComponents;
    unsigned char *data = stbi_load(file_path, &width, &height, &nComponents, 4);

    Texture tex = TextureLoadPro(data, width, height);

    stbi_image_free(data);

    return tex;
}

Texture TextureLoadPro(unsigned char *data, int width, int height) {
    Texture tex;
    tex.width = width;
    tex.height = height;
    tex.data = data;

    glGenTextures(1, &tex.id);
    glBindTexture(GL_TEXTURE_2D, tex.id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    if (data != NULL) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        printf("[Texture] Texture loaded successfully!\n");

        return tex;
    }
    printf("[!Texture] Failed to load texture!\n");

    return tex;
}
