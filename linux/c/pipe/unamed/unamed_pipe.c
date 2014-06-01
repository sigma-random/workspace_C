#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<string.h>

#define BUF_SIZE 1024
#define true 1

static void sig_handler(int signum)
{
    int status;
    switch(signum)
    {
        case SIGCHLD:
            waitpid(-1, &status,WNOHANG);
            printf("receive child exit signal\n");
            exit(EXIT_SUCCESS);
            break;
        case SIGALRM:
            printf("\n[*] new messge\n");
            break;
    }

}

int main(int argc, char **argv)
{

    int fd[2];
    pid_t pid;
    int rd_count = 0;
    int wt_count = 0;
    char buf[BUF_SIZE];

    signal(SIGCHLD,sig_handler);
    signal(SIGALRM,sig_handler);
    if(-1 == pipe(fd))
    {
        perror("pipe");
        exit(-1);
    }
    if(-1 == (pid = fork()))
    {
        perror("fork");
        exit(-1);
    }
    if(0 == pid)    //child process
    {
        close(fd[1]);   //close write pipe    
        while(true)
        {
            bzero(buf,BUF_SIZE);
            if( 0 < (rd_count = read(fd[0], buf,BUF_SIZE)))
            {
                write(STDOUT_FILENO, "receive from parent: ",21);
                write(STDOUT_FILENO, buf, rd_count);
                buf[rd_count-1] = 0;
                if(!strcmp(buf,"!quit"))
                {
                    write(STDOUT_FILENO, "child: start to exit!\n",22);
                    exit(0);
                }
                kill(getppid(), SIGALRM);
            }
        }
        exit(0);
    }
    //parent process
    close(fd[0]); //close read pipe
    while(true)
    {
        bzero(buf, BUF_SIZE);
        write(STDOUT_FILENO, "send to child: ", 15);
        if( 0< (rd_count = read(STDIN_FILENO, buf, BUF_SIZE)))
        {
            write(fd[1] , buf, rd_count); 
        }
        pause();
    }
    return 0;
}
