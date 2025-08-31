#pragma once

#include <glad/gl.h>

typedef struct Shader {
    GLuint vertId;
    GLuint fragId;
    GLuint programId;
} Shader;

extern const char *_default_vert_source;

extern const char *_default_frag_source;

Shader ShaderCreate(const char *vertSource, const char *fragSource);

Shader ShaderCreateDefault(void);
