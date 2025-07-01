#include "fat.h"
#include "WiiLibs.h"
#include <fat.h>

int devicepresent;

static void DetectFATdevice() {
    FILE* test = fopen("sd:/TEST", "w+");

    if (test == NULL) {
    
        devicepresent = -1;
        fclose(test);
    
    } else {
    
        devicepresent = 0;
        fclose(test);
        remove("sd:/TEST");
    
    }
    
    test = fopen("usb:/TEST", "w+");
    
    if (test == NULL) {
    
        fclose(test);
    
    } else {

        devicepresent += 2;    
        fclose(test);
        remove("usb:/TEST");
    
    }
}

void FATInit() {
    fatInitDefault();
    
    DetectFATdevice();
}