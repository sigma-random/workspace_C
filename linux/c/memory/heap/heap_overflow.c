#include<stdlib.h>
#include<stdio.h>
#include<string.h>


int main()
{

    char* p1 = malloc(8);
    char* p2 = malloc(8);
    char* p3 = malloc(8);
    strncpy(p1,"1234567",7);
    p1[7] = '\0';
    strncpy(p2,"1234567",7);
    p2[7] = '\0';
    strncpy(p3,"1234567",7);
    p3[7] = '\0';
    free(p3);
    getchar();
    free(p2);
    getchar();
    free(p1);
    getchar();
    getchar();
    return 0;

}
