#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

#define LOOP        50
#define BUF_SIZE    8192

char buf[BUF_SIZE];


int readBlock(int fd)
{
    int i = 0;
    int r_cnt = 0;

    for(i = 0; i < LOOP; i++)
    {
        r_cnt = read(fd,buf,BUF_SIZE);
        if(r_cnt == 0)
        {
            fprintf(stderr,"[+] @@@@@@@@@@@@@@@ read finish @@@@@@@@@\n");
            break;
        }
        if(r_cnt < 0 && errno == EINTR)
        {
            fprintf(stderr,"########## Interupt 0ops#########\n");
            continue;
            //i--;
        }
        if(r_cnt <= 0)
        {
            perror("read");
            continue;
        }
        /* do something which will take some time */
        sleep(1);
        fprintf(stderr,"[+] %d read %d bytes\n",i,r_cnt);
    }
    return 0;
}

int writeNonBlock(int fd)
{
    
    int i = 0;
    int flags = 0;
    int w_cnt = 0;

    flags = fcntl(fd,F_GETFL,0);
    if( -1 == fcntl(fd,F_SETFL,flags|O_NONBLOCK))
    {
        perror("fcntl F_SETFL");
        return -1;
    }
    for(i = 0; i < LOOP; i++)
    {
        w_cnt = write(fd,buf,BUF_SIZE);
        if(w_cnt <= 0)
        {
            perror("write");
        }
        else
        {
            fprintf(stderr,"[+] %d write %d bytes\n",i,w_cnt);
        }
    }
    return 0;
}

void signal_handler(int signum)
{
    int status;
    pid_t pid;

    switch(signum)
    {
        case SIGCHLD:       //this signal will make parent raise EINTR on read/write/accept and etc which some block functions
             while( 0 < (pid =waitpid(0,&status,WNOHANG)))
             {
                fprintf(stderr,"\n[+]*****detect process %d exit*****\n",pid);
                
             } 
              
        default:
             break;
    }

}

int main()
{
    pid_t pid;
    int fd[2];

    signal(SIGCHLD,signal_handler);

    if(-1 == pipe(fd))
    {
        perror("pipe!");
        return -1;
    }
    if(-1==(pid = fork()))
    {
        perror("fork!");
        return -1;
    }
    if(pid == 0)    //child process
    {
        close(fd[0]);   //close read pipe
        writeNonBlock(fd[1]);
        //while(1);
        exit(0);
    }
    //parent process
    close(fd[1]);       //close write pipe
    readBlock(fd[0]);

}
