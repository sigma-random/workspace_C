#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

/*
 *
 *  before you test "setuid", you should make this
 *program setuid mask  as root user;
 *             
 *       chmod     u+x 
 */




int main(int argc, char **argv)
{

        printf("before setuid(0)\n");
        printf("uid: %d\n",getuid());
        printf("sid: %d\n",getsid(getpid()));
        printf("euid: %d\n\n\n",geteuid());
        
        
        if(-1 == seteuid(0))
        {
            perror("seteuid(0) error!\n");
            return 0;
        }
        
        printf("\n\nafter setuid(0)\n");
        

        printf("uid: %d\n",getuid());
        printf("sid: %d\n",getsid(getpid()));
        printf("euid: %d\n\n\n",geteuid());
        system("/bin/sh");
        
        getchar();
        
        return 0;
 
}
