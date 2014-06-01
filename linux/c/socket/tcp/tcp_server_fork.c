#include "tcp.h"
#include<signal.h>

#define BUF_SIZE 1024
#define MAX_CONN 2


static void sig_handler(int signum)
{

    switch(signum)
    {
        case SIGCHLD:
                printf("detected child process exit!\n");
                break;
        case SIGALRM:
                break;
    }
}

void childProcess(const int sockfd, struct sockaddr_in *pSin)
{
    int client_sockfd = sockfd;
    struct sockaddr_in client_sin = *pSin;
    int rd_cnt, wt_cnt;
    char buf[BUF_SIZE];
    int i;
    char *client_ip;
    int client_port;
    
    bzero(buf, BUF_SIZE);
    client_ip = inet_ntoa(client_sin.sin_addr);
    client_port = ntohs(client_sin.sin_port);
    sprintf(buf,"remote client %s:%d\n", client_ip, client_port);
    write(STDOUT_FILENO, buf, strlen(buf));

    send(client_sockfd, "welcome to [R4nd0m] TcpServer\n", 30, 0);
    while(1)
    {
        bzero(buf ,BUF_SIZE);
        if( 0 >= (rd_cnt = (recv(client_sockfd, buf, BUF_SIZE, 0))))
        {
            //perror("[server-child] recv");
            exit(-1);
        }
        
        write(STDOUT_FILENO, "[", 1);
        write(STDOUT_FILENO, client_ip, strlen(client_ip));
        write(STDOUT_FILENO, " say] ", 6);
        write(STDOUT_FILENO, buf, rd_cnt);
        i = 0;
        while(i < rd_cnt)
        {
            buf[i] = toupper(buf[i]);
            i++;
        }
        if( 0 >= (wt_cnt = (send(client_sockfd, buf, rd_cnt, 0))))
        {
            // perror("[server-child] send");
            exit(-1);
        }
       
    }


}

void startTcpServer(char *ip, int port)
{
    struct sockaddr_in sin, client_sin;
    int sockfd, client_sockfd;
    pid_t pid;
    int isReuseAddr = 1;
    int len = 0;

    bzero(&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    inet_aton(ip, &sin.sin_addr);

    if( -1 ==(sockfd = socket(AF_INET, SOCK_STREAM, 0)))
    {
        perror("[server] socket");
        exit(-1);
    }

    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &isReuseAddr, sizeof(isReuseAddr));

    if(-1 == bind(sockfd, (struct sockaddr*)&sin, sizeof(sin)))
    {
        perror("[server] bind");
        exit(-1);
    }
            
    if( -1 == listen(sockfd, MAX_CONN))
    {
        perror("[server] listen");
        exit(-1);
    }
    printf("TcpServer listen @ %s:%d\n",ip,port);
    while(1)
    {

        bzero(&client_sin, sizeof(client_sin));
        len = sizeof(client_sin);
        client_sockfd = -1;
        if(-1 == (client_sockfd = accept(sockfd,(struct sockaddr*)&client_sin, &len)))
        {
            perror("[server] accept");
            exit(-1);
        }   

        if( -1 == (pid = fork()))
        {
            perror("[server] fork");
            exit(-1);
        }
        if(0 < pid) //child process
        {
            
            childProcess(client_sockfd, &client_sin);
            exit(0);
       
        }
        else    //parent process
        {
            close(client_sockfd);
        }

    }

}


int main(int argc, char **argv)
{
    int port;
    char ip[16];

    if(argc != 3)
    {
        printf("usage: %s ip port\n",argv[0]);
        exit(-1);
    }
    signal(SIGCHLD, sig_handler);
    strncpy(ip, argv[1], 16);
    port = atoi(argv[2]);
    startTcpServer(ip, port);
    return 0;
}
