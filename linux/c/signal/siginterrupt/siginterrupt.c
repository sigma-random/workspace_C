#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>

/*
 *
 *  EINTR will raise on some blocked fucntion(such as read/write/..), 
 *  after process recv signal and finished signal handler!!!!
 *
 *  so we must address this issue.
 *
 */

#define BUF_SIZE 8192
#define LOOP 10

char buf[BUF_SIZE];


void sig_handler(int signum)
{
    if(signum == SIGALRM)
    {
        fprintf(stderr,"[parent] recv SIGALRM signal!\n");
    }

}


int main()
{
    pid_t pid;
    int fd[2];

    siginterrupt(SIGALRM,0);
    signal(SIGALRM,sig_handler);

    if( -1 == pipe(fd))
    {
        perror("pipe");
        return -1;
    }


    if(-1 == (pid = fork()))
    {
        perror("fork");
        return -1;
    }

    if(0 == pid)    //child process
    {
        int i = 0;
        ssize_t w_cnt = 0;
        close(fd[0]);
        while( (i++ < LOOP)) {
            if( w_cnt = write(fd[1],buf,BUF_SIZE))
            {
                fprintf(stderr,"\n\n[%03d] child write %d bytes\n",i,BUF_SIZE);
            }
            kill(getppid(),SIGALRM);
        }
        fprintf(stderr,"\n\n[child] will exit!\n");
        exit(0);
    }
    //parent process
    ssize_t r_cnt = 0;
    close(fd[1]);
    sleep(1);
    while(1)
    {
        r_cnt = read(fd[0],buf,BUF_SIZE);
        if(r_cnt == 0)
        {
            fprintf(stderr,"read finished!\n");
            break;
        }
        if(r_cnt < 0 && errno == EINTR)
        {
            fprintf(stderr,"************* EINTER happed! ***********\n");
            perror("read");
            continue;
        }
        if(r_cnt < 0)
        {
            perror("read");
            break;
        }
        fprintf(stderr,"[parent] read %d bytes\n",r_cnt);
    }
    return 0;
}

