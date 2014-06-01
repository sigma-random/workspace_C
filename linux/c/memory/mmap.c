#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/mman.h>
#include<string.h>


typedef struct person
{
    int age;
    char name[20];

}Person,*pPerson;

int main(int argc, char **argv)
{
    pPerson p;    
    int size;
    int i;
    size = 10 * sizeof(Person);
    p = (pPerson)mmap((void*)0xb7fdf000, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1 ,0);
    for(i = 0; i < 10; i++)
    {
        (p+i)->age = 20 + i;
        snprintf((p+i)->name,10,"jack%d",i);
    }
    for(i = 0; i < 10; i++)
    {
       printf("%p --> age = %-05d  name = %-10s\n",p+i,(p+i)->age,(p+i)->name); 
    }
    //system("cat /proc/`pgrep mmap`/maps");
    getchar();
    return 0;
}


