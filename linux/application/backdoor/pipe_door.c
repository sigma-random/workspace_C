#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <cerrno>
#include <iostream>

using namespace std;

char buf[4096];

int main(int argc, char* argv[])
{
        pid_t pid;
        int fd[2];
        int status;
        int i;
        int test;
        if(argc != 2){
                cerr << "Usage: findprocess <name>" << endl;
                exit(1);
        }
        if(-1 == pipe(fd)) {
            perror("pipe");
            exit(-1);
        }
        pid = fork();
        if(pid < 0){
                perror("fork");
                exit(1);
        }
        if (pid == 0){  //child process
                //close(0);   
                close(fd[1]);   //close write pipe
                if(-1 == dup2(fd[0],0)) {
                    perror("dup2");
                    exit(0);
                }
                execl("/bin/grep","grep",argv[1],NULL);
                exit(-1);
        
        }else{
            //close(1);
            dup2(fd[1],1);  //write pipe
            close(fd[0]);   //close read pipe
            execl("/bin/ps","ps","all",NULL);
            wait(&status);
            fprintf(stderr,"finished!\n");
            getchar();
}
return 0;
}

