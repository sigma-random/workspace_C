#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define DEBUG 1

/* debugPrintf.c */
extern void debugPrintf(int debug, char *format, ...);

int main() {

    debugPrintf(DEBUG,"%s","hello world!\n");
    debugPrintf(~DEBUG,"%s","no printf!\n");
    return 0;

}
