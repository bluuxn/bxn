#pragma once

#include <glad/gl.h>

#include "platform.h"

#include "math/math.h"

#include "shader.h"
#include "texture.h"

#define MAX_VERTICES 2048
#define MAX_INDICES MAX_VERTICES * 6

typedef struct Vertex {
    Vec2 pos;
    Vec2 uv;
    Color color;
} Vertex;

typedef struct RenderBatch {
    GLuint vao;
    GLuint vbo;
    GLuint ebo;

    Shader shader;

    Vertex vertices[MAX_VERTICES];
    int vertexCount;

    int indices[MAX_INDICES];
    int indexCount;

    Texture curr_tex;
    Texture shape_tex;

    Mat4 proj;
} RenderBatch;

extern RenderBatch _rb;

void RenderInit(void);

void RenderDestroy(void);

void RenderClear(Color color);

void RenderBegin(void);

void RenderEnd(void);

void Present(void);

void RenderPushVertex(Vec2 pos, Vec2 uv, Color Color);

void RenderPushIndex(int a, int b, int c);

void RenderTriangle(Vec2 a, Vec2 b, Vec2 c, Color color);

void RenderQuad(Vec2 a, Vec2 b, Vec2 c, Vec2 d, Color color);

void RenderTexturePro(Texture tex, Rect src, Rect dest, Vec2 origin, float rotation, Color tint);

void RenderTextureRec(Texture tex, Rect src, Vec2 pos, Color tint);

void RenderTextureEx(Texture tex, Vec2 pos, float rotation, float scale, Color tint);

void RenderTextureV(Texture tex, Vec2 pos, Color tint);

void RenderTexture(Texture tex, float x, float y, Color tint);
