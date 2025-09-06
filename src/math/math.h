#pragma once

typedef struct Vec2 {
    float x, y;
} Vec2;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Vec4 {
    float x, y, z, w;
} Vec4;

typedef struct Mat4 {
    union {
        struct {
            float ax, ay, az, aw;
            float bx, by, bz, bw;
            float cx, cy, cz, cw;
            float dx, dy, dz, dw;
        };
        float v[16];
    };
} Mat4;

typedef struct Rect {
    float x, y, width, height;
} Rect;

typedef struct Color {
    unsigned char r, g, b, a;
} Color;

Mat4 Mat4Identity();

Mat4 Mat4Mult(Mat4 l, Mat4 r);

Mat4 Mat4Translate(float x, float y, float z);

Mat4 Mat4Scale(float x, float y, float z);

Mat4 Mat4RotateX(float angle);

Mat4 Mat4RotateY(float angle);

Mat4 Mat4RotateZ(float angle);

Mat4 Mat4Ortho(float left, float right, float bottom, float up, float znear, float zfar);

#define WHITE (Color){255, 255, 255, 255}
#define BLUUXN (Color){90, 120, 196, 255}
