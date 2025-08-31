#include "input.h"
#include "platform.h"
#include <GLFW/glfw3.h>
#include <stdbool.h>

int _prev_keys[GLFW_KEY_LAST + 1] = {0};
int _curr_keys[GLFW_KEY_LAST + 1] = {0};

void PollInput(void) {
    for (int i = 0; i <= GLFW_KEY_LAST; i++) {
        _prev_keys[i] = _curr_keys[i];
        _curr_keys[i] = glfwGetKey(_window, i);
    }
}

bool InputKeyDown(int key) {
    return (_curr_keys[key] == GLFW_PRESS);
}

bool InputKeyUp(int key) {
    return (_curr_keys[key] == GLFW_RELEASE);
}

bool InputKeyPressed(int key) {
    return (_curr_keys[key] == GLFW_PRESS && _prev_keys[key] == GLFW_RELEASE);
}

bool InputKeyReleased(int key) {
    return (_curr_keys[key] == GLFW_RELEASE && _prev_keys[key] == GLFW_PRESS);
}
