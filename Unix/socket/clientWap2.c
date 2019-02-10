#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 34986

int main(int argc, char const* argv[] )
{
    int sockfd=0;
    if( (sockfd=socket(AF_INET, SOCK_STREAM, 0))<0 )
    {
        printf("socket failed\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr,'0',sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);

    if( inet_pton(AF_INET,"118.89.140.143",&serv_addr.sin_addr)<=0 )
    {
        printf("invalid address\n");
        return -1;
    }

    if( connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0 )
    {
        printf("connect failed\n");
        return -1;
    }

    char* msg="msg from client";
    send(sockfd,msg,strlen(msg),0);
    printf("client msg sent\n");

    char buf[1024]={0};
    int valread=read(sockfd,buf,1024);
    printf("%s\n",buf);
    close(sockfd);

    return 0;
}
