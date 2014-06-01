#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<signal.h>
#include<limits.h>
#include<sys/stat.h>
#include<time.h>


#define FIFO_NAME "myfifo"
#define FIFO_BUF_SIZE 256

void sig_handler(int signum)
{
    switch(signum)
    {
        case SIGPIPE:
                printf("I'm in write fifo now\n");
                break;
    }
}

int main(int argc, char **argv)
{
    mode_t mode = 0644;
    int fd;
    int wt_cnt;
    int rd_cnt;
    char buf[FIFO_BUF_SIZE];
    time_t mytime;
    char *sTime;



    signal(SIGPIPE, sig_handler);
    if( -1 == mkfifo(FIFO_NAME,mode))
    {
        perror("[write pipe]: mkfifo");
        exit(EXIT_FAILURE);
    }

    if(-1 == (fd = open(FIFO_NAME,O_RDONLY)))
    {
        perror("[read pipe]: open");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        bzero(buf,FIFO_BUF_SIZE);
        //write(STDOUT_FILENO, "[read fifo] msg:", 17);
        if(0 > (rd_cnt = read(fd, buf, FIFO_BUF_SIZE)))
        {
            perror("[read pipe]: read");
            exit(EXIT_FAILURE);
        }
                
        write(STDOUT_FILENO, buf, rd_cnt);
    }
    return 0;
}


