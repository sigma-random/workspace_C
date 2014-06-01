#include "io.h"


int main (int argc, char **argv)
{

    int fd; 
    int num,len;
    char *buf;
    if(argc != 2)
    {
        printf("usge: %s filename\n",argv[0]);
        exit(-2);
    }
    if(-1 == (fd = open(argv[1], O_CREAT | O_RDWR | O_TRUNC,MODE(0,6,4,4))))
    {
       perror("can't creat!\n");
       exit(-1);
    }
    buf = malloc(1024);
    if(buf <= 0 )
    { 
        perror("mallo error!\n");
        exit(-1);
    }
    printf("input:");
    scanf("%s",buf);
    len = strlen(buf);
    num = write(fd, buf, len);
    //lseek(fd,len,SEEK_SET);
    //lseek(fd,len,SEEK_CUR);
    //lseek(fd,len,SEEK_END);
    //lseek(fd,0,SEEK_SET);
    lseek(fd,100,SEEK_SET);
    printf("input:");
    scanf("%s",buf);
    len = strlen(buf);
    num = write(fd, buf, len);

    free(buf);
    close(fd);
    return 0;
}
