#include<stdlib.h>
#include<stdio.h>


int main()
{

    char* p1 = malloc(7);
    strcpy(p1,"1111111");
    char* p2 = malloc(9);
    strcpy(p2,"222222222");
    char* p3 = malloc(17);
    strcpy(p3,"33333333333333333");
    free(p3);
    free(p2);
    getchar();
    free(p1);
    return 0;

}
