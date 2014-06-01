#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>


#define MODE_755  ((7<<6)|(5<<3)|(5)) // 755
#define MODE_4755  ((4<<9)|(7<<6)|(5<<3)|(5)) // 4755

int main(int argc, char **argv)
{
    
    char *in,*out;
    int fd;
    if(argc != 2)
    {
        printf("usage: %s filename\n",argv[0]);
        exit(-1);
    }
    if(argv[1] != NULL)
    {
        in = argv[1];
    }
    fd = open(in,O_RDWR | O_CREAT, MODE_4755);
    return 0;       
}
