#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

#define MODE_644    ((6<<6)|(4<<3)|(4))

int main(int argc, char **argv)
{
    
    int fd;
    if(argc != 2)
    {
        printf("usage: %s filename\n",argv[0]);
        exit(-1);
    }
    if( -1 == (fd = open(argv[1],O_CREAT | O_RDWR | O_APPEND ,MODE_644)))
    {
        perror("create/ open file error!\n");
        exit(-1);
    }
    printf("fd = %d\n",fd);
    system("ls -al   /proc/`pgrep dup2`/fd/");
    write(fd, "hello", 5);
    dup2(STDOUT_FILENO, fd);    //fd will redirect to STDOUT, instead of file descriptor
    printf("fd = %d\n",fd);
    system("ls -al   /proc/`pgrep dup2`/fd/");
    write(fd, "world", 5);
    getchar();
    close(fd);
    return 0;

}
