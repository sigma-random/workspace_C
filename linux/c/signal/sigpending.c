#include<signal.h>
#include<stdio.h>
#include<stdlib.h>

static void sig_handler(int signum)
{

    int delay = 20;
    switch(signum)
    {
        case SIGINT:
                printf("SIGINT: go to sleep:-)\n");
                sleep(delay);
                printf("SIGINT: go to weak up:-)\n");
                break;
        case SIGQUIT:
                printf("SIGQUIT: recieve SIGQUIT\n");
                break;
        case SIGSTOP:
                printf("SIGSTOP: recieve SIGSTOP\n");
                break;
        default:
                printf("recieve sig: %d\n",signum);
                break;
    }
}
int main(int argc, char **argv)
{

    sigset_t set;
    sigset_t old_set, new_set;
    sigemptyset(&new_set);
    sigemptyset(&old_set);
    sigaddset(&new_set, SIGINT);
    sigaddset(&new_set, SIGQUIT);
    sigaddset(&new_set, SIGSTOP);
    signal(SIGINT,sig_handler);
    signal(SIGSTOP,sig_handler);
    signal(SIGQUIT,sig_handler);
    sigprocmask(SIG_BLOCK, &new_set, &old_set);
    printf("start pending signal: SIGINT SIGQUIT\n");
    sleep(10);
    printf("stop pending signal: SIGINT SIGQUIT\n");
    sigprocmask(SIG_SETMASK, &old_set, NULL);
    while(1)
    {
        sleep(1);
    }
    return 0;
}
