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

#define BUF_SIZE 1024
#define _FILE   "/etc/shadow"

char buf[BUF_SIZE] = {0};


int  readFile(char *filename) {
    
    struct stat st;
    int fd;
    int r_cnt = 0;

    if(-1 == stat(filename ,&st)) {
        perror("stat");
        return -1;
    }
    if(st.st_mode & S_IFREG || st.st_mode & S_IFLNK) {

        if(-1 == (fd = open(filename, O_RDONLY))) {
            perror("open");
            return -1;
        }
        memset(buf, 0, BUF_SIZE);
        while(1) {
            r_cnt = read(fd, buf, BUF_SIZE);
            if(r_cnt <= 0) {
                break;
            }
            write(STDOUT_FILENO, buf, r_cnt);
        }
        return 0;
    }
    printf("not a file!\n");
    return -1;
}

int main(int argc, char **argv)
{

        printf("before setuid(0)\n");
        printf("uid: %d\n",getuid());
        printf("sid: %d\n",getsid(getpid()));
        printf("euid: %d\n\n\n",geteuid());
        
        if(-1 == readFile(_FILE)) {
            perror("readfile");
            return -1;
        }
        
        if(-1 == seteuid(0))
        {
            perror("seteuid(0) error!\n");
            return 0;
        }
        
        printf("\n\nafter setuid(0)\n");
        

        printf("uid: %d\n",getuid());
        printf("sid: %d\n",getsid(getpid()));
        printf("euid: %d\n\n\n",geteuid());
        
        if(-1 == readFile(_FILE)) {
            perror("readfile");
            return -1;
        }
        
        getchar();
        
        return 0;
 
}
