#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <vector>
#include <iostream>
#include "common.h"
std::string WPA2_encrypt(std::string nonce,std::string tk,std::string text);

int main()
{
    int fd1[2],fd2[2];
    pid_t pid;
    int ret;
    int r=0;
    std::vector<std::string> digits{"0","1","2","3","4","5","6","7","8","9","10"};
    ret= pipe(fd1);
    if(ret== -1)
    {
        perror("pipe1.\n");
        exit(1);
    }
    ret= pipe(fd2);
    if(ret== -1)
    {
        perror("pipe2.\n");
        exit(1);
    }
    pid= fork();
    if(pid== -1)
    {
        perror("fork.\n");
        exit(1);
    }
    else if(pid== 0)    // server
    {
        char buff[256];
        close(fd1[1]);
        close(fd2[0]);

        // recv 1st request
        read(fd1[0],buff,256);
        std::cout<<"Server recv: "<<buff<<std::endl;
        std::string ANonce=genRand(128,0,0);
        char msg[1024]={0};
        // send ANonce
        memcpy(msg,ANonce.c_str(),ANonce.size());
        write(fd2[1],msg,strlen(msg)+ 1);
        // send r
        std::string r_str(digits[r++]);
        memcpy(msg,r_str.c_str(),r_str.size());
        msg[r_str.size()]=0;
        write(fd2[1],msg,strlen(msg)+ 1);

        // recv CNonce
        read(fd1[0],buff,256);
        std::cout<<"Server recv cnonce: "<<buff<<std::endl;
        std::string cnonce(buff);

        // recv tk
        read(fd1[0],buff,256);
        std::cout<<"Server recv tk: "<<buff<<std::endl;
        std::string tk(buff);

        // verify TK
        std::string t=ANonce+cnonce;
        std::string auth_TK=genMd5(t);
        if(auth_TK==tk) std::cout<<"verification tk success"<<std::endl;
        else 
        {
            std::cout<<"tk disgrees!"<<std::endl;
            return 1;
        }

        // send ack
        std::string ACK("ack_from_server");
        memcpy(msg,ACK.c_str(),ACK.size());
        msg[ACK.size()]=0;
        write(fd2[1],msg,strlen(msg)+ 1);

        // recv ack
        read(fd1[0],buff,256);
        std::cout<<"Server recv ack: "<<buff<<std::endl;
        std::string ack(buff);

        std::string Nonce;
        int n=0;

        // recv 1st hello
        Nonce=digits[n++];
        read(fd1[0],buff,256);
        std::cout<<"Server recv : "<<buff<<std::endl;
        std::string cipher(buff);
        auto decry=WPA2_encrypt(Nonce,tk,cipher);
        std::cout<<"Server decrypt : "<<decry<<std::endl;

         // recv 2nd hello
        Nonce=digits[n++];
        read(fd1[0],buff,256);
        std::cout<<"Server recv : "<<buff<<std::endl;
        cipher=std::string(buff);
        decry=WPA2_encrypt(Nonce,tk,cipher);
        std::cout<<"Server decrypt : "<<decry<<std::endl;




        close(fd1[0]);
        close(fd2[1]);
    }
    else    // client
    {
        char buff[1024]={0};
        close(fd1[0]);
        close(fd2[1]);
        int i= 0;
        char msg[1024]={0};
        // send 1st request
        memcpy(msg,"Authentification_Request",strlen("Authentification_Request"));
        write(fd1[1],msg,strlen(msg)+ 1);

        // recv ANonce
        read(fd2[0],buff,512);  
        std::cout<<"Client recv ANonce: "<<buff<<std::endl;
        std::string anonce(buff);

        // recv r
        read(fd2[0],buff,512);
        std::cout<<"Client recv r="<<buff<<std::endl;

        // send CNonce
        std::string CNonce=genRand(128,0,0);
        memcpy(msg,CNonce.c_str(),CNonce.size());
        msg[CNonce.size()]=0;
        write(fd1[1],msg,strlen(msg)+ 1);
        sleep(1);
        // send TK
        std::string t=anonce+CNonce;
        std::string TK=genMd5(t);
        memcpy(msg,TK.c_str(),TK.size());
        msg[TK.size()]=0;
        write(fd1[1],msg,strlen(msg)+ 1);

        // recv ack
        read(fd2[0],buff,512);
        std::cout<<"Client recv ack: "<<buff<<std::endl;

        // send ack
        std::string ACK{"ACK_from_client"};
        memcpy(msg,ACK.c_str(),ACK.size());
        msg[ACK.size()]=0;
        write(fd1[1],msg,strlen(msg)+ 1);

        // init
        std::string EncryptKey(TK);
        std::string Nonce;
        
        int n=0;
        // send first msg
        Nonce=digits[n++];
        std::cout<<"client send: hello"<<std::endl;
        std::string hello{"hello"};
        auto enc=WPA2_encrypt(Nonce,TK,hello);
         std::cout<<"client fisrt encrypt: "<<enc<<std::endl;
        memcpy(msg,enc.c_str(),enc.size());
        msg[enc.size()]=0;
        write(fd1[1],msg,strlen(msg)+ 1);

        sleep(1);

        // send 2nd hello
        Nonce=digits[n++];
        std::cout<<"client send: hello"<<std::endl;
        enc=WPA2_encrypt(Nonce,TK,hello);
        std::cout<<"client second encrypt: "<<enc<<std::endl;
        memcpy(msg,enc.c_str(),enc.size());
        msg[enc.size()]=0;
        write(fd1[1],msg,strlen(msg)+ 1);

      
        
       

        close(fd1[1]);
        close(fd2[0]);
        int status;
        wait(&status);
    }
    return 0;
}

int char2int(char c)
{
    if(c=='0')return 0;
    if(c=='1')return 1;
    if(c=='2')return 2;
    if(c=='3')return 3;
    if(c=='4')return 4;
    if(c=='5')return 5;
    if(c=='6')return 6;
    if(c=='7')return 7;
    if(c=='8')return 8;
    if(c=='9')return 9;
    if(c=='a' || c=='A')return 10;
    if(c=='b' || c=='B')return 11;
    if(c=='c' || c=='C')return 12;
    if(c=='d' || c=='D')return 13;
    if(c=='e' || c=='E')return 14;
    if(c=='f' || c=='F')return 15;
    std::cout<<"trans error"<<std::endl;
    std::cout<<(unsigned int)c<<std::endl;

    throw 1;
}

char int2char(int a)
{
    if(a==0)return '0';
    if(a==1)return '1';
    if(a==2)return '2';
    if(a==3)return '3';
    if(a==4)return '4';
    if(a==5)return '5';
    if(a==6)return '6';
    if(a==7)return '7';
    if(a==8)return '8';
    if(a==9)return '9';
    if(a==10)return 'a';
    if(a==11)return 'b';
    if(a==12)return 'c';
    if(a==13)return 'd';
    if(a==14)return 'e';
    if(a==15)return 'f';
    std::cout<<"int2char err"<<std::endl;
    throw 1;
}

std::string WPA2_encrypt(std::string nonce,std::string tk,std::string text)
{
    std::string mac{"843A723D3A"};
    std::string IV=mac+nonce;
    std::string str;
    std::string fine;

    int a=text.size();

    if(text.empty())return fine;
    
    str=genMd5(IV+tk);
    if(text.size()%128)
    {
        int pr=128 - (text.size()%128);
        std::string padding(pr,'0');
        text+=padding;
    }
    
    if(text.size()%128)
    {
        std::cout<<"padding error"<<std::endl;
        throw 1;
    }
    
    for(int i=0;i<text.size();++i)
    fine+= char2int(str[i%32]) ^ text[i];
    return fine;

    
}