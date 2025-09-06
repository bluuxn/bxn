#include "renderer.h"

#include "math/math.h"

#include <math.h>

#include <glad/gl.h>

#include "input.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

RenderBatch _rb = {};

void RenderInit(void) {
    glGenVertexArrays(1, &_rb.vao);
    glBindVertexArray(_rb.vao);

    glGenBuffers(1, &_rb.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _rb.vbo);

    glGenBuffers(1, &_rb.ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rb.ebo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * MAX_VERTICES, NULL, GL_DYNAMIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * MAX_INDICES, NULL, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
            sizeof(Vertex), (void*)offsetof(Vertex, pos));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE,
            sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
            sizeof(Vertex), (void*)offsetof(Vertex, uv));

    _rb.shader = ShaderCreateDefault();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    unsigned char shape_data[4] = {255, 255, 255, 255};
    _rb.shape_tex = TextureLoadPro(shape_data, 1, 1);

    int width, height;
    WindowGetSize(&width, &height);
    _rb.proj = Mat4Ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);
    _rb.view = Mat4Identity();

    _rb.uProj = glGetUniformLocation(_rb.shader.programId, "uProj");
    _rb.uView = glGetUniformLocation(_rb.shader.programId, "uView");

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void RenderDestroy(void) {
    glDeleteVertexArrays(1, &_rb.vao);
    glDeleteBuffers(1, &_rb.vbo);
    glDeleteBuffers(1, &_rb.ebo);
}

void RenderClear(Color color) {
    glClearColor((float)color.r / 255.0, (float)color.g / 255.0,
            (float)color.b / 255.0, (float)color.a / 255.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void RenderBegin(void) {
    _rb.vertexCount = 0;
    _rb.indexCount = 0;
}

void RenderEnd(void) {
    if (_rb.indexCount == 0) return;
    glBindVertexArray(_rb.vao);
    glBindBuffer(GL_ARRAY_BUFFER, _rb.vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rb.ebo);
    glUseProgram(_rb.shader.programId);
    glBindTexture(GL_TEXTURE_2D, _rb.curr_tex.id);
    glUniformMatrix4fv(_rb.uProj, 1, GL_FALSE, &_rb.proj.ax);
    glUniformMatrix4fv(_rb.uView, 1, GL_FALSE, &_rb.view.ax);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * _rb.vertexCount,
            _rb.vertices);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(int) * _rb.indexCount,
            _rb.indices);

    glDrawElements(GL_TRIANGLES, _rb.indexCount, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Present(void) {
    glfwSwapBuffers(_window);
    glfwPollEvents();
    PollInput();
}

void RenderSetProjection(Mat4 proj) {
    _rb.proj = proj;
}

void RenderPushVertex(Vec2 pos, Vec2 uv, Color color) {
    _rb.vertices[_rb.vertexCount].pos = pos;
    _rb.vertices[_rb.vertexCount].uv = uv;
    _rb.vertices[_rb.vertexCount].color = color;
    _rb.vertexCount++;
}

void RenderPushIndex(int a, int b, int c) {
    _rb.indices[_rb.indexCount++] = a;
    _rb.indices[_rb.indexCount++] = b;
    _rb.indices[_rb.indexCount++] = c;
}

void RenderTriangle(Vec2 a, Vec2 b, Vec2 c, Color color) {
    if (_rb.curr_tex.id != _rb.shape_tex.id || _rb.vertexCount+3 >= MAX_VERTICES
        || _rb.indexCount+3 >= MAX_INDICES) {
        RenderEnd();
        RenderBegin();
        glBindTexture(GL_TEXTURE_2D, _rb.shape_tex.id);
        _rb.curr_tex = _rb.shape_tex;
    }

    const int initialCount = _rb.vertexCount;

    RenderPushVertex(a, (Vec2){0, 1}, color);
    RenderPushVertex(b, (Vec2){0, 0}, color);
    RenderPushVertex(c, (Vec2){1, 0}, color);

    RenderPushIndex(initialCount+0, initialCount+1, initialCount+2);
}

void RenderQuad(Vec2 a, Vec2 b, Vec2 c, Vec2 d, Color color) {
    if (_rb.curr_tex.id != _rb.shape_tex.id || _rb.vertexCount+4 >= MAX_VERTICES
            || _rb.indexCount+6 >= MAX_INDICES) {
        RenderEnd();
        RenderBegin();
        glBindTexture(GL_TEXTURE_2D, _rb.shape_tex.id);
        _rb.curr_tex = _rb.shape_tex;
    }

    const int initialCount = _rb.vertexCount;

    RenderPushVertex(a, (Vec2){0, 1}, color);
    RenderPushVertex(b, (Vec2){0, 0}, color);
    RenderPushVertex(c, (Vec2){1, 0}, color);
    RenderPushVertex(d, (Vec2){1, 1}, color);

    RenderPushIndex(initialCount+0, initialCount+1, initialCount+2);
    RenderPushIndex(initialCount+3, initialCount+2, initialCount+0);
}

void RenderRect(Rect rect, Color color) {
    RenderQuad((Vec2){rect.x, rect.y}, (Vec2){rect.x, rect.y+rect.height},
            (Vec2){rect.x+rect.width, rect.y+rect.height}, (Vec2){rect.x+rect.width, rect.y},
            color);
}

void RenderTexturePro(Texture tex, Rect src, Rect dest, Vec2 origin, float rotation, Color tint) {
    if (_rb.curr_tex.id != tex.id || _rb.vertexCount+4 >= MAX_VERTICES
            || _rb.indexCount+6 >= MAX_INDICES) {
        RenderEnd();
        RenderBegin();
        glBindTexture(GL_TEXTURE_2D, tex.id);
        _rb.curr_tex = tex;
    }

    float u0 = src.x / (float)tex.width;
    float v0 = src.y / (float)tex.height;
    float u1 = (src.x + src.width) / (float)tex.width;
    float v1 = (src.y + src.height) / (float)tex.height;

    Vec2 corners[4] = {
        { -origin.x, -origin.y },
        { dest.width - origin.x, -origin.y },
        { dest.width - origin.x, dest.height - origin.y },
        { -origin.x, dest.height - origin.y }
    };

    float cosR = cosf(rotation);
    float sinR = sinf(rotation);

    for (int i = 0; i < 4; i++) {
        float x = corners[i].x;
        float y = corners[i].y;
        corners[i].x = x * cosR - y * sinR + dest.x;
        corners[i].y = x * sinR + y * cosR + dest.y;
    }

    int startIndex = _rb.vertexCount;

    RenderPushVertex(corners[0], (Vec2){u0, v0}, tint);
    RenderPushVertex(corners[1], (Vec2){u1, v0}, tint);
    RenderPushVertex(corners[2], (Vec2){u1, v1}, tint);
    RenderPushVertex(corners[3], (Vec2){u0, v1}, tint);

    RenderPushIndex(startIndex + 0, startIndex + 1, startIndex + 2);
    RenderPushIndex(startIndex + 2, startIndex + 3, startIndex + 0);
}

void RenderTextureRec(Texture tex, Rect src, Vec2 pos, Color tint) {
    RenderTexturePro(tex, src, (Rect){pos.x, pos.y,
            tex.width, tex.height}, (Vec2){0, 0}, 0, tint);
}

void RenderTextureEx(Texture tex, Vec2 pos, float rotation, float scale, Color tint) {
    RenderTexturePro(tex, (Rect){0, 0, tex.width, tex.height},
            (Rect){pos.x, pos.y, tex.width*scale, tex.height*scale}, (Vec2){0, 0}, rotation, tint);
}

void RenderTextureV(Texture tex, Vec2 pos, Color tint) {
    RenderTextureEx(tex, pos, 0, 1, tint);
}

void RenderTexture(Texture tex, float x, float y, Color tint) {
    RenderTextureV(tex, (Vec2){x, y}, tint);
}
