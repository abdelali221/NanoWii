#ifndef _FILEUTILS_H_
#define _FILEUTILS_H_

#include "WiiLibs.h"

void printfilecontent(FILE **file, const char *filename);
void printfilesize(FILE **file);
void safe_fclose(FILE **file);

#endif