#include "fileutils.h"
#include "TUI.h"
#include "Video.h"
#include "WiiLibs.h"

void printfilecontent(FILE **file, const char *filename) {
    if (!file) return;

    struct stat st;

    int fd = fileno(*file);
    
    if (fstat(fd, &st) != 0) return;
    
    off_t file_size = st.st_size;

    ClearScreen();

    printTopbar(filename);

    POSCursor(0, 3);

    rewind(*file);

    int ch;
    
    for (off_t i = 0; i < file_size; i++) {
        ch = fgetc(*file);
        
        if (ch == EOF || ch == '\0')
            break;

        if (ch == '\n') {
    
            if (conY > 24)
                Scroll(filename);
            else
                POSCursor(conX, conY);

            putchar('\n');
    
        } else {

            if (conY > 25 && conX == 75)
                Scroll(filename);
            else
                POSCursor(conX, conY);

            putchar(ch);
            
        }

        CON_GetPosition(&conX, &conY);
    }

    CON_GetPosition(&conX, &conY);

    POSCursor(40, 28);
    
    printf("%lld Bytes", (long long)file_size);

    POSCursor(conX, conY);
}

void safe_fclose(FILE **file) {
    if (file && *file) {
        fclose(*file);
        *file = NULL;
    }
}