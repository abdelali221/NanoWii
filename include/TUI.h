#ifndef _TUI_H_
#define _TUI_H_

#include <stddef.h>

#define VER "v1.0"

#define WHITE_BG_BLACK_FG "\x1b[47;1m\x1b[30m"
#define DEFAULT_BG_FG "\x1b[40m\x1b[37m"

extern int conX;
extern int conY;

void printCurrentPos(char *buffer, size_t location);
void printTopbar(const char *filename);
void Scroll(const char *filename);
void ShowCursor();

#endif