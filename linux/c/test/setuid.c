#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/**
 * before run it , this binary file must be setuid(0) by chmod +s command
 *
 */

 int main(int argc, char **argv) {

    char buf[255];
    pid_t old_uid,e_uid;
    bzero(buf, 255);


    old_uid = getuid();
    e_uid = geteuid();
    printf("before:  uid = %d euid = %d \n",old_uid, e_uid);
    
    //get root privileges
    setuid(e_uid);
    printf("after: uid = %d euid = %d \n",getuid(), geteuid());
    
    strcpy(buf,"/bin/cat /etc/shadow ");
    system(buf);
    
    //drop root privileges
    setuid(old_uid);
    printf("after drop privileges: uid = %d euid = %d \n",getuid(), geteuid());
    system(buf);
    
    return 0;
}
