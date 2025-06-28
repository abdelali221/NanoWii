#include "fatsystem.h"
#include "Input.h"
#include "TUI.h"
#include "Video.h"
#include "WiiLibs.h"

char filename[64] = "Untitled";

char filepath[255];

int conX;
int conY;

FILE* file;

void printTopbar() {
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

void ShowCursor() {
    printf("%s %s", WHITE_BG_BLACK_FG, DEFAULT_BG_FG);
    POSCursor(conX, conY);
}

void Scroll() {
    POSCursor(0, 28);
    
    printf("              ");
    
    putchar('\n');
    
    printTopbar();
    
    POSCursor(0, 25);
}

void Openfile() {
    ClearScreen();
    
    fclose(file);
    
    char chr = 0;
    bool stayinloop = true;

    printTopbar();
    
    printf("\nEnter the file directory : ");
    
    int i = 0;
    
    memset(filepath, 0, sizeof(filepath)); 
    
    while (i < sizeof(filepath)) {   
    
        chr = 0;
        chr = getchar();
    
        if (chr > 31) {
    
            putchar(chr);
            filepath[i] = chr;
            i++;
    
        } else if (chr == '\r') {
            
            if (filepath[i - 1] != '/') {
            
                filepath[i] = '/';
                filepath[i + 1] = '\0'; 
            
            } else {
            
                filepath[i] = '\0';
            
            }
            
            break;
    
        } else if (chr == '\b' && i > 0) {
    
            printf("\b \b");
            i--;
    
        }
    
    }
    
    if (toupper(filepath[0]) != 'U' || toupper(filepath[1]) != 'S' || toupper(filepath[2]) != 'B' || filepath[3] != ':' || filepath[4] != '/') {
    
        if (toupper(filepath[0]) != 'S' || toupper(filepath[1]) != 'D' || filepath[2] != ':' || filepath[3] != '/') {
    
            fclose(file);
            printf("\nInvalid Dir!");
            usleep(2*(10e5));
            Openfile();
    
        }
    
    }
    
    if (devicepresent == 1) {
    
        if (toupper(filepath[0]) == 'U' && toupper(filepath[1]) == 'S' && toupper(filepath[2]) == 'B') {
    
            fclose(file);
            printf("\nDevice Unavailable!");
            usleep(2*(10e5));
            Openfile();
    
        }
    
    } else if (devicepresent == 0) {
        
        if (toupper(filepath[0]) == 'S' && toupper(filepath[1]) == 'D') {
    
            fclose(file);
            printf("Device Unavailable!");
            usleep(2*(10e5));
            Openfile();
    
        }
    }

    printf("\nDir = %s", filepath);
    struct stat sb;

    if (stat(filepath, &sb) != 0 && !(S_ISDIR(sb.st_mode))) {

        printf("\nDo you want to create the directory? Y/N \n");
        char dir[255];
        memset(dir, 0, sizeof(dir));

        while (stayinloop)
        {
            switch (toupper(getchar()))
            {
                case 'Y':
                    stayinloop = false;
                break;
            
                case 'N':
                    return;
                break;
            }
        }
        
        while (1) {

            int j = 0;

            while (filepath[j] != '\0') {

                while (filepath[j] != '/') {
                    
                    j++;

                }

                j++;

                strncpy(dir, filepath, j);

                if (stat(dir, &sb) == 0 && S_ISDIR(sb.st_mode)) {

                    printf("\r%s", dir);

                } else {
                    mkdir(dir, 0755);
                    printf("\nCreated %s", dir);
                }

            }

            break;
            
        }

    }

    printf("\nEnter the file name : ");
    
    i = 0;
    
    memset(filename, 0, sizeof(filename)); 
    
    while (i < sizeof(filename))
    {   
        chr = 0;
        chr = getchar();
    
        if (chr > 31) {
    
            putchar(chr);
            filename[i] = chr;
            i++;
    
        } else if (chr == '\r') {
    
            filename[i] = '\0';
            break;
    
        } else if (chr == '\b') {
    
            printf("\b \b");
            i--;
            filename[i] = 0;
    
        }
    }
    
    strcat(filepath, filename);
    
    printf("\n%s Is that correct? Y/N", filepath);
    
    stayinloop = true;
    
    while (stayinloop)
    {
        switch (toupper(getchar()))
        {
            case 'Y':
                stayinloop = false;
            break;
        
            case 'N':
                Openfile();
            break;
        }
    }

    ClearScreen();
    
    printTopbar();

    file = fopen(filepath, "w+");
    
    if (file == NULL) fclose(file);    
    
    return;
}

void Ctrlhandle() {
    CON_GetPosition(&conX, &conY);
    
    POSCursor(20, 28);
    
    printf("You Pressed CTRL");
    
    while (1)
    {

        switch (toupper(getchar()))
        {
            case 0x03:
                POSCursor(20, 28);
                printf("%*c", 17, ' ');
                POSCursor(conX, conY);
                return;
            break;
            
            case 'O':
                Openfile();
                return;
            break;

            default:
            break;
        }

    }

}

int main(void) {
    VideoInit();
    
    InputInit();
    
    FATInit();
    
    printTopbar();
    
    strcat(filepath, filename);
    
    file = fopen(filepath, "w+");
    
    if (file == NULL) fclose(file);
    
    printCurrentPos();

    ShowCursor();
    
    while(1) {
    
        char keyinput = getchar();
    
        switch (keyinput)
        {
            case 0x1b:
        
                fclose(file);
                exit(0);
            
            break;
        
            case '\b':
        
                printf("\b \b");
                truncate(filepath, sizeof(file) - 1);

            break;
        
            case 13:
        
                if (conY > 24) {
                    Scroll();
                } else {
                    POSCursor(conX, conY);
                }
        
                printf("\n");
                fprintf(file, "\n");
            
            break;
        
            case 0x03:
        
                Ctrlhandle();
                keyinput = 0;
            
            break;
        
            default:
                
                if (keyinput > 31) {
                    if (conY > 25 && conX == 75) {
                        Scroll();
                    } else {
                        POSCursor(conX, conY);
                    }

                    printf("%c", keyinput);
                    fprintf(file, "%c", keyinput);
                }

            break;
        }

        printCurrentPos();
        
        ShowCursor();
    
        VIDEO_WaitVSync();
    }

    return 0;
}