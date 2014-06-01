#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<syslog.h>


void writeLog()
{
    int i = 0;
    openlog("r4dn0m", LOG_PID | LOG_CONS, LOG_USER | LOG_INFO | LOG_DEBUG);
    for(i = 0; i < 3 ; i++)
    {
        syslog(LOG_INFO,"this is log%d from r4nd0m\n",i);
        sleep(1);
    }
    closelog();
}


int main(int argc, char **argv)
{
    writeLog();
    system("tail /var/log/syslog");
    return 0;
}
