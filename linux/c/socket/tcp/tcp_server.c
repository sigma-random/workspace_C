#include "tcp.h"

#define BUF_SIZE 1024

void startTcpServer(const char *ip, const int port)
{
    struct sockaddr_in sin, client_sin;
    int sockfd, client_sockfd;
    char buf[BUF_SIZE];
    int len = 0;
    int rd_cnt, wt_cnt;
    int i = 0;
    int isReuseSock = 1;

    bzero(&sin,sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = INADDR_ANY;   // hton(ip);
    
    /* 1. build sock*/
    if( -1 == (sockfd = socket(AF_INET, SOCK_STREAM, 0)))
    {
        perror("socket");
        exit(0);
    }

    /* 2. reuse socket*/
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &isReuseSock, sizeof(isReuseSock));

    /* 3. bind sock with ip/port */
    if( -1 == bind(sockfd,(struct sockaddr*)&sin, sizeof(sin)))
    {
        perror("bind");
        exit(-1);
    }

    /* 4. listen sock*/
    if(-1 == listen(sockfd, 10))
    {
        perror("listen");
        exit(-1);
    }
    printf("TcpServer listen: ip = %s   port = %d \n",ip,port);
    while(1)
    {
        len = sizeof(client_sin);
        /* 5. wait for client to connect */
        if(-1 == ( client_sockfd = accept(sockfd, (struct sockaddr*)&client_sin, &len)) )
        {
            perror("listen");
            exit(-1);
        }
        printf("client accept: ip = %s   port = %d \n",inet_ntoa(client_sin.sin_addr),ntohs(client_sin.sin_port));
        write(client_sockfd, "welcome to [R4nd0m] TcpServer\n",30);
        while(1)
        {
/*
            bzero(buf, BUF_SIZE);
            write(STDOUT_FILENO, "[server say] ", 13);
            if( 0 >= (rd_cnt = read(STDIN_FILENO, buf, BUF_SIZE)))
            {
                perror("[server] read");
                exit(-1);
            }
            if( 0 >= (wt_cnt = write(client_sockfd, buf, rd_cnt)))
            {
                perror("[server] write");
                exit(-1);
            }
*/
            bzero(buf, BUF_SIZE);
            write(STDOUT_FILENO, "[client say] ", 13);
            //if( 0 > (rd_cnt = read(client_sockfd, buf, BUF_SIZE)))
            if( 0 >= (rd_cnt = recv(client_sockfd, buf, BUF_SIZE, 0)))
            {
                perror("[server] read");
                exit(-1);
            }
            write(STDOUT_FILENO, buf, rd_cnt);
            i = 0;
            while(i < rd_cnt)
            {
                buf[i] = toupper(buf[i]);
                i++;
            }
            //if( 0 >= write(client_sockfd, buf, strlen(buf)))
            if(-1 == send(client_sockfd, buf, strlen(buf), 0))
            {
                perror("[server send]");
                exit(-1);
            }
        }
        close(client_sockfd);
    }

}

int main(int argc, char ** argv)
{
    char ip[16];  //192.168.111.111
    int port;
    if(argc != 3)
    {
        printf("usage: %s ip port\n",argv[0]);
        exit(-1);
    }
    strncpy(ip, argv[1], 16);
    port = atoi(argv[2]);
    startTcpServer(ip, port);
    return 0;
}
