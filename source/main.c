#include "fatsystem.h"
#include "fileutils.h"
#include "Input.h"
#include "TUI.h"
#include "Video.h"
#include "WiiLibs.h"

char filename[64] = "Untitled";

char filepath[255];

FILE* file;

int Openfile() {
    ClearScreen();
    
    fclose(file);
    
    char chr = 0;
    bool stayinloop = true;

    printTopbar(filename);
    
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
            return -1;
    
        }
    
    }
    
    if (devicepresent == 2) {
    
        if (toupper(filepath[0]) == 'U' && toupper(filepath[1]) == 'S' && toupper(filepath[2]) == 'B') {
    
            fclose(file);
            printf("\nDevice Unavailable!");
            usleep(2*(10e5));
            return -1;
    
        }
    
    } else if (devicepresent == -1) {
        
        if (toupper(filepath[0]) == 'S' && toupper(filepath[1]) == 'D') {
    
            fclose(file);
            printf("Device Unavailable!");
            usleep(2*(10e5));
            return -1;
    
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
                    return -2;
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
    
    while (stayinloop) {

        switch (toupper(getchar())) {

            case 'Y':
            
                stayinloop = false;
            
            break;
        
            case 'N':

                return -1;

            break;
        }
    }

    file = fopen(filepath, "r+");

    if (file) {
    
        printfilecontent(&file, filename);
    
    } else {

        ClearScreen();
        printTopbar(filename);
        file = fopen(filepath, "w+");

        if (!file) {

            printf("Failed to open file!\n");

        }
    }

    return 0;
}

void Ctrlhandle() {
    CON_GetPosition(&conX, &conY);
    
    POSCursor(20, 28);
    
    printf("You Pressed CTRL");
    
    while (1)
    {

        switch (toupper(getchar())) {

            case 0x03:

                POSCursor(20, 28);
                printf("%*c", 17, ' ');
                POSCursor(conX, conY);
                return;
            
            break;
            
            case 'O':

                while (1)
                {
                    int ret = Openfile();
                    if (ret == 0)                
                        break;

                }                
                
                return;

            break;

            default:
            break;
        }
    }
}

int main(void) {
    InputInit();
    
    VideoInit();
    
    FATInit();
    
    printTopbar(filename);

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
        
                printf(" \b\b \b");
                truncate(filepath, sizeof(file) - sizeof(char));

            break;
        
            case 13:
        
                if (conY > 24) {

                    putchar(' ');
                    Scroll(filename);

                } else {

                    POSCursor(conX, conY);

                }
        
                printf(" \b\n");
                fprintf(file, "\n");
            
            break;
        
            case 0x03:
        
                Ctrlhandle();
                keyinput = 0;
            
            break;
        
            default:
                
                if (keyinput > 31) {

                    if (conY > 25 && conX == 76) {

                        putchar(' ');
                        Scroll(filename);

                    } else {

                        POSCursor(conX, conY);

                    }

                    printf("%c", keyinput);
                    fprintf(file, "%c", keyinput);
                }

            break;
        }

        printCurrentPos();

        printfilesize(&file);
        
        ShowCursor();
    
        VIDEO_WaitVSync();
    }

    return 0;
}