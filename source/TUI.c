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
    
    int realtextsize = 0;
    
    for (realtextsize = 0; realtextsize < sizeof(filename); realtextsize++) {
    
        if (filename[realtextsize] == 0) break;
    
    }
    
    realtextsize++;
    
    printf("%s%6c%s%3c%s%*c%s%*c", WHITE_BG_BLACK_FG, ' ', "NANOWII", ' ', VER, 20 - (realtextsize/2), ' ', filename, 38 - (realtextsize/2), ' ');

    CON_GetPosition(&conX, &conY);

    while (conX != 0)
    {
        putchar(' ');
    }
        
    printf("\n");

    printf("%s", DEFAULT_BG_FG);

}

void Scroll(const char *filename) {
    POSCursor(0, 28);
    
    printf("              ");
    
    putchar('\n');
    
    printTopbar(filename);
    
    POSCursor(0, 25);
}

void ShowCursor() {
    printf("%s %s", WHITE_BG_BLACK_FG, DEFAULT_BG_FG);
    POSCursor(conX, conY);
}