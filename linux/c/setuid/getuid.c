#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>


int main(int argc, char **argv)
{
    
        printf("uid: %d\n",getuid());
        printf("gid: %d\n",getegid());
        printf("sid: %d\n",getsid(getpid()));
        printf("euid: %d\n",geteuid());
        getchar();
        return 0;
 
}
