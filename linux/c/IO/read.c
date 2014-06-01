#include "io.h"


int main(int argc, char **argv)
{
    
    int fd;
    ssize_t rd_count;
    char buf[1024];
    if(argc != 2)
    {
        printf("usage: %s filename\n",argv[0]);
        exit(-1);
    }
           
    if(0 > (fd = open(argv[1], O_RDONLY)))
    {
        perror("can't open file\n");
        exit(-1);
    }
    do
    {
        if(-1 == (rd_count = read(fd, buf, 1024)))
        {
            printf("can't read or read finished\n");
            break;
        }
        printf("%s",buf);
        memset(buf,0,1024);
    
    }while(rd_count > 0);
    printf("\n");
    close(fd);
    return 0;
    
}
