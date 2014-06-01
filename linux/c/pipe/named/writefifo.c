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
                printf("Broken pipe was Brken!\n");
                exit(-1);
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
    /*
    if( -1 == mkfifo(FIFO_NAME,mode))
    {
        perror("[write pipe]: mkfifo");
        exit(EXIT_FAILURE);
    }
    */
    if(-1 == (fd = open(FIFO_NAME,O_WRONLY)))
    {
        perror("[write pipe]: open");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        bzero(buf,FIFO_BUF_SIZE);
        mytime = time(NULL);
        sTime = ctime(&mytime);
        sprintf(buf, "[wirte fifo] %s\n",sTime);
        //write(STDOUT_FILENO, "[write fifo] msg:", 17);
        if(0 > (rd_cnt = read(STDIN_FILENO, buf, FIFO_BUF_SIZE)))
        {
            perror("[write pipe]: read");
            exit(EXIT_FAILURE);
        }
                
        if( 0 > ( wt_cnt = write(fd, buf, rd_cnt)) )
        {
            perror("[write pipe]: write");
            exit(EXIT_FAILURE);
        }

        sleep(0.5);
    }
    return 0;
}


