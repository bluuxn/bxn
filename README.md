# bxn
## This is a game library that I make to learn OpenGL

## Example
```c
#include <bxn.h>

int main() {
    WindowInit(640, 360, "Hello bxn!");

    RenderInit();

    Texture tex = TextureLoad("res/my_texture.png");

    while (WindowRunning()) {
        RenderBegin();
        RenderClear(BLUUXN);

        RenderRect((Rect){0, 0, 16, 16});
        RenderTexture(tex, 32, 32);

        RenderEnd();
    }

    RenderDestroy();
    WindowDestroy();
}
```

## Features
- Opening window
- Rendering triangle
- Rendering rectangle
- Rendering texture
- Batch rendering
- Input handling (but still using GLFW_KEY constants)

## Goals
- Rendering texts
- Collision
- Audio
- Physics
- Many more
