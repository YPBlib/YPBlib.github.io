#include "serverWap2.h"
int main(int argc,char const* argv[])
{
    int server_fd;
    if((server_fd=socket(AF_INET,SOCK_STREAM,0))==0)
    {
	perror("server socket failed\n");
	exit(EXIT_FAILURE);
    }
    extern "C"
    {
        struct sockaddr_in address;
    }
    

    // set socket opt
    int opt=1;
    if( setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt)) )
    {
	perror("set port failed\n");
	exit(EXIT_FAILURE);
    }
    address.sin_family=AF_INET;
    address.sin_addr.s_addr=INADDR_ANY;
    address.sin_port=htons(PORT);

    if( bind(server_fd,(struct sockaddr*)&address,sizeof(address))<0 )
    {
	perror("bind failed\n");
	exit(EXIT_FAILURE);
    }
    printf("bind ok \n");

    if( listen(server_fd,1024)<0 )
    {
	perror("listen failed\n");
	exit(EXIT_FAILURE);
    }
    
    printf("listen ok\n");
    int new_socket;
    int addrlen=sizeof(address);
    if( (new_socket=accept(server_fd,(struct sockaddr*)&address,(socklen_t*)&addrlen))<0 )
    {
	printf("accept failed\n");
	exit(EXIT_FAILURE);
    }
   
    printf("accept() success\n");
    int valread;
    char buffer[1024]={0};
    char* msg="Hello World!\n";
    
    // read bytes from new socket
    valread=read(new_socket,buffer,1024);
    printf("%s\n",buffer);
    send(new_socket,msg,strlen(msg),0);
    printf("done\n");

    return 0;
}
