#pragma once

#include <GLFW/glfw3.h>

#include <stdbool.h>

extern int _prev_keys[GLFW_KEY_LAST+1];
extern int _curr_keys[GLFW_KEY_LAST+1];

void PollInput(void);

bool InputKeyDown(int key);

bool InputKeyUp(int key);

bool InputKeyPressed(int key);

bool InputKeyReleased(int key);
