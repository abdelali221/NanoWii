#include "Input.h"
#include "WiiLibs.h"
#include "Video.h"
#include <wiikeyboard/keyboard.h>

void keypress(char keyinput) {
    if (keyinput == 0x1b)
        exit(0);
}

void InputInit() {
    KEYBOARD_Init(keypress);
}