#include "common.h"
#include <string>


int main(int argc,char** argv)
{
    if(argc!=5)
    {
        printf("usage: ./client <ip> <port> <passwd> <file>\n");
        return -1;
    }

    std::string ip(argv[1]);
    int port(atoi(argv[2]));
    std::string passwd(argv[3]);
    std::string file(argv[4]);

    std::string welcome_msg{"Authentication_Request"};
    if(Wap2CliendSend("118.89.140.143","31601",welcome_msg.c_str())==Ret_Success)
    {
        std::string ANonce(Wap2CliendRecv("118.89.140.143","31601"));
    }
    else
    {
        printf("Authentication_Request Sent Failed\n");
        return -1;
    }


    return 0;
}