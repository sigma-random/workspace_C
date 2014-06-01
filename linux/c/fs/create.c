#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>


#define MODE_755  ((7<<6)|(5<<3)|(5)) // 755
#define MODE_644  ((6<<6)|(4<<3)|(4)) // 644
#define MODE_4755  ((4<<9)|(7<<6)|(5<<3)|(5)) // 4755

int main(int argc, char **argv)
{
    
    char *in,*out;
    int fd;
    ssize_t count;
    char * msg = "hello world";
    if(argc != 2)
    {
        printf("usage: %s filename\n",argv[0]);
        exit(-1);
    }
    if(argv[1] != NULL)
    {
        in = argv[1];
    }
    fd = open(in,O_RDWR | O_CREAT, MODE_644);
    if(-1 == (count = write(fd, msg, strlen(msg))) )
    {
        perror("write error!\n");
    }
    printf("write %d bytes to file %s\n",count,in);
    close(fd);
    return 0;       
}
