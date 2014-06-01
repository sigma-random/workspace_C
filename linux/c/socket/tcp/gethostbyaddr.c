#include<netdb.h>
#include"tcp.h"



int main(int argc, char** argv)
{
    char *ip;
    char *hostname;
    struct hostent *ht;
    struct in_addr addr;

    if(2 != argc)
    {
        printf("usage: %s ip\n",argv[0]);
        exit(0);
    }
    ip = argv[1];
    if(0 >= inet_pton(AF_INET, ip,&addr))
    {
        perror("inet_pton");
        exit(-1);
    }

    ht = gethostbyaddr((const char*)&addr, sizeof(addr), AF_INET);
    if(NULL == ht)
    {
        perror("gethostbyaddr");
        exit(-1);
    }
    printf("ip = %s    domain = %s\n",ip,ht->h_name);

    return 0;
}
