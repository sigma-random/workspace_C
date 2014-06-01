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
    
    char *in, *out;
    int fd_in, fd_out;
    ssize_t rd_count, wr_count, total = 0;
    char *buf[1024];
    char * msg = "hello world";
    if(argc != 3)
    {
        printf("usage: %s infile outfile\n",argv[0]);
        exit(-1);
    }
    in = argv[1];
    out = argv[2];
    fd_in = open(in,O_RDONLY);
    fd_out = open(out,O_RDWR|O_CREAT,MODE_644);
    if(fd_in<0)
    {
        printf("can't open infile:%s\n",in);
        exit(-1);
    }
    if(fd_out<0)
    {
        printf("can't open/create outfile:%s\n",out);
        exit(-1);
    }
    while(0 < (rd_count = read(fd_in,buf,8)))
    {
        total += rd_count;
        while( (wr_count = write(fd_out, buf,rd_count)) < rd_count\
                && wr_count)
        {
            rd_count -= wr_count;
        }
        if(wr_count < 0)
        {
            perror("write error!\n");
            exit(-2);
        }
    
    }
    printf("write %d bytes to file %s\n",total,out);
    close(fd_in);
    close(fd_out);
    return 0;       
}
