#include "Input.h"
#include "WiiLibs.h"
#include "Video.h"
#include <wiikeyboard/keyboard.h>

void keypress(char key) {}

void InputInit() {
    KEYBOARD_Init(keypress);
}