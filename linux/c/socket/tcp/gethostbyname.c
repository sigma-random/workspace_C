#include<netdb.h>
#include"tcp.h"


int main(int argc, char **argv)
{

    char *hostname;
    struct hostent *ht;
    char **addr_list;
    char ip[INET_ADDRSTRLEN];

    if(2 != argc)
    {
        printf("usage: %s hostname\n",argv[0]);
        exit(0);
    }
    hostname = argv[1];
    ht = gethostbyname(hostname);
    addr_list = ht->h_addr_list;
    while(*addr_list)
    {
        inet_ntop(AF_INET,(struct addr_in*)*addr_list,ip,INET_ADDRSTRLEN);
        printf("host = %s  ip = %s\n",ht->h_name,ip);
        addr_list++;
    }
}
