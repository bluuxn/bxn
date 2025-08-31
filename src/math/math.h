#pragma once

#include <cglm/struct.h>

typedef vec2s Vec2;

typedef vec3s Vec3;

typedef vec4s Vec4;

typedef mat4s Mat4;

typedef struct Rect {
    float x, y, width, height;
} Rect;

typedef struct Color {
    unsigned char r, g, b, a;
} Color;

Mat4 Mat4Ortho(float left, float right, float bottom, float up, float znear, float zfar);

#define WHITE (Color){255, 255, 255, 255}
#define BLUUXN (Color){90, 120, 196, 255}
