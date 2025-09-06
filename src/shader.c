#include "shader.h"

#include <glad/gl.h>

#include <stdio.h>
#include <stdlib.h>

#include "math/math.h"

#include "platform.h"

const char *_default_vert_source =
"#version 460 core\n"
"layout(location = 0) in vec2 aPos;\n"
"layout(location = 1) in vec4 aColor;\n"
"layout(location = 2) in vec2 aUV;\n"
"out vec4 vColor;\n"
"out vec2 vUV;\n"
"uniform mat4 uProj;\n"
"uniform mat4 uView;\n"
"void main() {\n"
"  gl_Position = uProj * uView * vec4(aPos, 0, 1);\n"
"  vColor = aColor;\n"
"  vUV = aUV;\n"
"}\0";

const char *_default_frag_source =
"#version 460 core\n"
"in vec4 vColor;\n"
"in vec2 vUV;\n"
"out vec4 fColor;\n"
"uniform sampler2D uTex;\n"
"void main() {\n"
"  fColor = texture(uTex, vUV) * vColor;\n"
"}\0";

Shader ShaderCreate(const char *vertSource, const char *fragSource) {
    Shader shdr = {};

    GLint success;

    printf("[Shader] Creating new shader!\n");

    shdr.programId = glCreateProgram();
    glUseProgram(shdr.programId);
    printf("[Shader] Created shader program with id %d\n", shdr.programId);

    shdr.vertId = glCreateShader(GL_VERTEX_SHADER);
    printf("[Shader] Created vertex shader with id %d!\n", shdr.vertId);
    glShaderSource(shdr.vertId, 1, &vertSource, NULL);
    glCompileShader(shdr.vertId);
    printf("[Shader] Checking for vertex shader error!\n");
    glGetShaderiv(shdr.vertId, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        GLint logLength;
        glGetShaderiv(shdr.vertId, GL_INFO_LOG_LENGTH, &logLength);
        GLchar *log = (GLchar*)malloc(logLength);
        glGetShaderInfoLog(shdr.vertId, logLength, NULL, log);
        printf("[!Shader] Error found!\n%s\n", log);
        free(log);
    }
    printf("[Shader] Vertex shader compiled without error!\n");

    shdr.fragId = glCreateShader(GL_FRAGMENT_SHADER);
    printf("[Shader] Created fragment shader with id %d!\n", shdr.fragId);
    glShaderSource(shdr.fragId, 1, &fragSource, NULL);
    glCompileShader(shdr.fragId);
    printf("[Shader] Checking for fragment shader error!\n");
    glGetShaderiv(shdr.fragId, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        GLint logLength;
        glGetShaderiv(shdr.fragId, GL_INFO_LOG_LENGTH, &logLength);
        GLchar *log = (GLchar*)malloc(logLength);
        glGetShaderInfoLog(shdr.fragId, logLength, NULL, log);
        printf("[!Shader] Error found!\n%s\n", log);
        free(log);
    }
    printf("[Shader] Fragment shader compiled without error!\n");

    glAttachShader(shdr.programId, shdr.vertId);
    glAttachShader(shdr.programId, shdr.fragId);

    glLinkProgram(shdr.programId);

    glUseProgram(0);

    return shdr;
}

Shader ShaderCreateDefault(void) {
    Shader defaultShader = ShaderCreate(_default_vert_source, _default_frag_source);

    return defaultShader;
}
