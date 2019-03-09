#include <signal.h>
#include <stdio.h>

void sigHandler(int signum)
{
    printf("recv %d\n",signum);
}

int main(int argc,char* argv[])
{
    signal(SIGINT,sigHandler);
    while(1);
    return 0;
}

