#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>


void signal_handler(int signum){

    printf("signum = %d\n",signum);


}


int main() {


    signal(SIGINT,signal_handler);
    signal(SIGKILL,signal_handler);
    signal(SIGSTOP,signal_handler);
    signal(SIGTERM,signal_handler);
    signal(SIGQUIT,signal_handler);
    getchar();
    return 0;

}
