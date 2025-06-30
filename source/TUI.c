#include "TUI.h"
#include "Video.h"
#include "WiiLibs.h"

int conX;
int conY;

void printCurrentPos() {
    CON_GetPosition(&conX, &conY);
    
    POSCursor(0, 27);
    
    printf("%s", WHITE_BG_BLACK_FG);
    
    if (conX < 10) {
    
        printf("0%d", conX); 
    
    } else {
    
        printf("%d", conX);
    
    }
    
    printf(", ");
    
    if (conY - 2 < 10) {
    
        printf("0%d", conY - 2); 
    
    } else {
    
        printf("%d", conY - 2);
    
    }
    
    printf("%s", DEFAULT_BG_FG);
    
    POSCursor(conX, conY);
}

void printTopbar(const char *filename) {
    POSCursor(0, 0);
    
    printf("%s%6c%s%3c%s%*c%s", WHITE_BG_BLACK_FG, ' ', "NANOWII", ' ', VER, 18 - (sizeof(filename)/2), ' ', filename);

    CON_GetPosition(&conX, &conY);

    while (conX < 77 && conY == 0)
    {
        putchar(' ');
        CON_GetPosition(&conX, &conY);
    }
        
    printf("\n");

    printf("%s", DEFAULT_BG_FG);

    POSCursor(0, 2);
}

void Scroll(const char *filename) {
    POSCursor(0, 28);
    
    printf("%*c", ' ', 77);
    
    putchar('\n');
    
    printTopbar(filename);
    
    POSCursor(0, 25);
}

void ShowCursor() {
    printf("%s %s", WHITE_BG_BLACK_FG, DEFAULT_BG_FG);
    POSCursor(conX, conY);
}