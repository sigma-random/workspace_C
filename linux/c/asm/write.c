#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define __NR_write 4

char * msg = "hello world!\n";
char *shellcode = "\x90\x90\x90\x90\xCC";

int main() {
    
    int w_cnt;

    asm volatile(   "movl %1,%%ebx;\n"
                    "movl %2,%%ecx\n"
                    "movl %3,%%edx\n"
                    "movl %4,%%eax\n"
                    "int  $0x80\n"
                    "movl %%eax,%0"
                    :"=r"(w_cnt)
                    :"b"(1),"c"(msg),"d"(strlen(msg)),"a"(__NR_write)
                    );

    printf("w_cnt = %d\n",w_cnt);
    getchar();
    return 0;

}
