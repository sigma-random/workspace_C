#include "io.h"

int main (int argc, char **argv)
{

    int fd; 
    ssize_t total;
    int flag;
    if(argc != 2)
    {
        printf("usage: %s filename\n",argv[0]);
        exit(-1);
    }
    flag = O_CREAT | O_RDWR | O_TRUNC | O_APPEND;
    if(0> ( fd = (open(argv[1],flag,MODE(0,6,4,4)))))
    {
           perror("can't creat file\n");
           exit(-1);
    }
    write(fd, "hello", 5);
    lseek(fd, 0, SEEK_SET); /* O_APPEND is set , it will append to tail anyway*/
    
    flag = fcntl(fd, F_GETFL) & (~O_APPEND);
    fcntl(fd, F_SETFL, flag);
   
    write(fd, "world", 5);
    close(fd);
    return 0;
}
