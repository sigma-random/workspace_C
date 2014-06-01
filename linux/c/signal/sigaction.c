#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<sys/types.h>
#include<unistd.h>


/*
 *  note:-)
 *      sigaction can pennging other signals when there are one signal handler is running,
 *      you can test that enter "ctrl+\" when SIGINT is handling.
 *
 *                                                                              by Random
 */
 static void sig_handler(int signum)
{
    switch(signum)
    {
        case SIGINT:
                printf("SIGINT: recieve SIGINT\n");
                printf("SIGINT: start to sleep 30s\n");
                sleep(30);
                printf("SIGINT: start to weak up\n");
                break;
        case SIGQUIT:
                printf("SIGQUIT: recieve SIGQUIT\n");
                break;
        defaut:
                printf("recieve signal: %d\n",signum);
    
    }

}

int main()
{
    struct sigaction sigact;
    sigset_t sigmask;
    sigemptyset(&sigact.sa_mask);
    sigaddset(&sigact.sa_mask,SIGINT);
    sigaddset(&sigact.sa_mask,SIGQUIT);
    sigact.sa_handler = sig_handler;
    sigact.sa_flags = SA_NODEFER;
    if(sigaction(SIGINT,&sigact,NULL) == SIG_ERR)
    {
        perror("can't catch SIGINT\n");
    }
    if(sigaction(SIGQUIT,&sigact,NULL) == SIG_ERR)
    {
        perror("can't catch SIGQUIT\n");
    }
   
    printf("start to sleep\n");
    while(1)
    {
        sleep(1);
    }
    printf("start to weak up\n");


    return 0;
}
