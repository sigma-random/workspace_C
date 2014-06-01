#include<stdlib.h>
#include<stdio.h>

#define PAGE_SIZE 1024
int bss_data;

int main()
{
    char* pmem =(char*) malloc(32);
    int* p;
    strncpy(pmem,"12345678",8);
    printf("%s\n",pmem);
    printf("bss_data = %p    pmem = %p\n",&bss_data , pmem);
    free(pmem);
    //p = sbrk(0); 
    //p = sbrk(0);  //append heap 1 pages memory
    //printf("cur sbrk addr = %p\n",p);
    brk((int)((int*)&bss_data)+2048);
    pmem =(char*) malloc(32);
    free(pmem);
    getchar();
    return 0;
}
