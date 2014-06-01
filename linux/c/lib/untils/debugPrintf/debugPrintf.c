#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>

#define DEBUG 1

void debugPrintf(int isDebug, char* format, ...)
{
    va_list list_ptr;
    isDebug = isDebug <= 0 ? 0 :isDebug;
    if(isDebug) {
        va_start(list_ptr,format);
        vprintf(format,list_ptr);
        va_end(list_ptr);
    }
}

/*
int main() {

    debugPrintf(DEBUG,"%s","hello world!\n");
    debugPrintf(~DEBUG,"%s","hello world!\n");
    return 0;


}
*/
