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

    rewind(*file);

    ClearScreen();

    printTopbar(filename);
    
    for (off_t i = 0; i < file_size; i++) {
        int ch = fgetc(*file);
        
        if (ch == EOF || ch == '\0')
            break;

        if (ch == '\n') {
    
            if (conY > 26) {

                Scroll(filename);
            
            } else {

                POSCursor(conX, conY);

            }

            putchar('\n');
    
        } else {

            if (conY == 24 && conX == 77) {

                Scroll(filename);
            
            } else {

                POSCursor(conX, conY);
            
            }

            putchar(ch);   
        }

        CON_GetPosition(&conX, &conY);
    }

    printfilesize(file);
}

void printfilesize(FILE **file) {
    struct stat st;

    int fd = fileno(*file);

    if (fstat(fd, &st) != 0) return;

    off_t file_size = st.st_size;

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