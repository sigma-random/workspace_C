#include "tcp.h"

#define BUF_SIZE  256

void connectTcpServer(char *ip, int port)
{
    struct sockaddr_in server_sin;
    int sockfd;
    char buf[BUF_SIZE];
    int rd_cnt, wt_cnt;
    int len;

    bzero(&server_sin,sizeof(server_sin));
    server_sin.sin_family = AF_INET;
    server_sin.sin_port = htons(port);
    inet_aton(ip, &server_sin.sin_addr);

    if(-1 == (sockfd = socket(AF_INET, SOCK_STREAM, 0)))
    {
        perror("client: socket");
        exit(-1);
    }
    if( -1 == connect(sockfd,(struct sockaddr*)&server_sin,sizeof(server_sin)))
    {
        perror("client: connect");
        exit(-1);
    }
    while(1)
    {
        bzero(buf, BUF_SIZE);
        if(-1 == ( rd_cnt = recv(sockfd, buf, rd_cnt, 0)))
        {
            perror("client: write STDOUT");
            exit(-1);
        }
        write(STDOUT_FILENO, buf, rd_cnt);
        
        bzero(buf,BUF_SIZE);
        write(STDOUT_FILENO, "[To Server]: ", 13);
        if( 0 >= (rd_cnt = read(STDIN_FILENO, buf, BUF_SIZE)))
        {
            perror("client: read STDIN");
            exit(-1);
        }
        if( -1 == send(sockfd, buf, rd_cnt, 0))
        {
            perror("client: socket");
            exit(-1);
        }
        
    
    }

   
}


int main(int argc, char **argv)
{

    char ip[16];
    int port;
    if(argc != 3)
    {
        printf("usage: %s ip port\n",argv[0]);
        exit(-1);
    }
    strncpy(ip, argv[1], 16);
    port = atoi(argv[2]);
    connectTcpServer(ip, port);
    return 0;
}
