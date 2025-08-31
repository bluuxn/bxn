#include "math.h"

#include <cglm/struct.h>

Mat4 Mat4Ortho(float left, float right, float bottom, float top, float znear, float zfar) {
    return glms_ortho(left, right, bottom, top, znear, zfar);
}
