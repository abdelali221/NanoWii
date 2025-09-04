#include "TUI.h"
#include "Video.h"
#include "WiiLibs.h"

int conX;
int conY;

void printCurrentPos(char *buffer, size_t location) {
    CON_GetPosition(&conX, &conY);
    
    POSCursor(0, 27);

    u32 ROW = 0;
    u32 COL = 0;

    for(size_t i=0; i != location; i++) {

        if(buffer[i] == '\n') ROW++;
        
    }

    if(ROW != 0) {

        for(size_t i = location; buffer[i] != '\n'; i--) {

            COL++;

        }

    } else {

        COL = location;

    }
    
    printf("%s %d, %d%s  ", WHITE_BG_BLACK_FG, ROW, COL, DEFAULT_BG_FG);
    
    POSCursor(conX, conY);
}

void printTopbar(const char *filename) {
    POSCursor(0, 0);
    
    printf("%s%6c%s%3c%s%*c%s", WHITE_BG_BLACK_FG, ' ', "NANOWII", ' ', VER, 18 - (strlen(filename)/2), ' ', filename);

    CON_GetPosition(&conX, &conY);

    while (conX < 77 && conY == 0) {

        putchar(' ');
        CON_GetPosition(&conX, &conY);
    
    }
        
    printf("\n");

    printf("%s", DEFAULT_BG_FG);

    POSCursor(0, 2);
}

void Scroll(const char *filename) {
    POSCursor(0, 28);
    
    printf("%*c", 76, ' ');
    
    putchar('\n');
    
    printTopbar(filename);
    
    POSCursor(0, 25);
}

void ShowCursor() {
    printf("%s %s", WHITE_BG_BLACK_FG, DEFAULT_BG_FG);

    POSCursor(conX, conY);
}