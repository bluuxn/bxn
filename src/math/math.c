#include "math.h"
#include <math.h>

#include <stdio.h>

Mat4 Mat4Identity() {
    return (Mat4){
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1
    };
}

Mat4 Mat4Mult(Mat4 l, Mat4 r) {
    Mat4 m;

    m.ax = l.ax * r.ax + l.ay * r.bx + l.az * r.cx + l.aw * r.dx;
    m.ay = l.ax * r.ay + l.ay * r.by + l.az * r.cy + l.aw * r.dy;
    m.az = l.ax * r.az + l.ay * r.bz + l.az * r.cz + l.aw * r.dz;
    m.aw = l.ax * r.aw + l.ay * r.bw + l.az * r.cw + l.aw * r.dw;
    m.bx = l.bx * r.ax + l.by * r.bx + l.bz * r.cx + l.bw * r.dx;
    m.by = l.bx * r.ay + l.by * r.by + l.bz * r.cy + l.bw * r.dy;
    m.bz = l.bx * r.az + l.by * r.bz + l.bz * r.cz + l.bw * r.dz;
    m.bw = l.bx * r.aw + l.by * r.bw + l.bz * r.cw + l.bw * r.dw;
    m.cx = l.cx * r.ax + l.cy * r.bx + l.cz * r.cx + l.cw * r.dx;
    m.cy = l.cx * r.ay + l.cy * r.by + l.cz * r.cy + l.cw * r.dy;
    m.cz = l.cx * r.az + l.cy * r.bz + l.cz * r.cz + l.cw * r.dz;
    m.cw = l.cx * r.aw + l.cy * r.bw + l.cz * r.cw + l.cw * r.dw;
    m.dx = l.dx * r.ax + l.dy * r.bx + l.dz * r.cx + l.dw * r.dx;
    m.dy = l.dx * r.ay + l.dy * r.by + l.dz * r.cy + l.dw * r.dy;
    m.dz = l.dx * r.az + l.dy * r.bz + l.dz * r.cz + l.dw * r.dz;
    m.dw = l.dx * r.aw + l.dy * r.bw + l.dz * r.cw + l.dw * r.dw;

    return m;
}

Mat4 Mat4Translate(float x, float y, float z) {
    Mat4 m = Mat4Identity();
    m.dx = x;
    m.dy = y;
    m.dz = z;
    return m;
}

Mat4 Mat4Scale(float x, float y, float z) {
    Mat4 m = Mat4Identity();
    m.ax = x;
    m.by = y;
    m.cz = z;
    return m;
}

Mat4 Mat4RotateX(float angle) {
    float c = cosf(angle);
    float s = sinf(angle);
    Mat4 m = Mat4Identity();
    m.by = c;  m.bz = -s;
    m.cy = s;  m.cz = c;
    return m;
}

Mat4 Mat4RotateY(float angle) {
    float c = cosf(angle);
    float s = sinf(angle);
    Mat4 m = Mat4Identity();
    m.ax = c;  m.az = s;
    m.cx = -s; m.cz = c;
    return m;
}

Mat4 Mat4RotateZ(float angle) {
    float c = cosf(angle);
    float s = sinf(angle);
    Mat4 m = Mat4Identity();
    m.ax = c;  m.ay = -s;
    m.bx = s;  m.by = c;
    return m;
}

Mat4 Mat4Ortho(float left, float right, float bottom, float top, float znear, float zfar) {
    Mat4 m = Mat4Identity();

    m.ax = 2.0f / (right - left);
    m.by = 2.0f / (top - bottom);
    m.cz = -2.0f / (zfar - znear);

    m.dx = -(right + left) / (right - left);
    m.dy = -(top + bottom) / (top - bottom);
    m.dz = -(zfar + znear) / (zfar - znear);

    return m;
}
