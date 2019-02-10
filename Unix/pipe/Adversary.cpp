#include <sys/types.h>
#include <sys/stat.h>
#include <sys/termios.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <string>
#include <vector>
#include <iostream>
#include "common.h"
std::string WPA2_encrypt(std::string nonce,std::string tk,std::string text);
int char2int(char c);
char int2char(int a);
using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;

#define	MAXLINE	4096

int main()
{
	int		n;
	int		fd[2];
	pid_t	pid;
	char	line[MAXLINE];
	vector<string> dict{"POST","GET","HTTP","INPUT","OUTPUT"};
	// 假设 server 和 client 已经完成握手步骤
	string anonce{"9917DE8A617E8A3C01590103003F9D3C"};
    string cnonce{"DD54858C929A4D09DF8ECB16255CDEB9"};
    string tk{"e841614305a8d984ca673118c5810c0b"};
	vector<string> digits{"0","1","2","3","4","5","6","7","8","9","10"};

 
	if (pipe(fd) < 0)printf("pipe error");
	if ((pid = fork()) < 0) printf("fork error");
	
	else if (pid > 0)  // Client
	{		
		close(fd[0]);
		char msg[4096]={0};
		string cipher;
		string Nonce=digits[0];
		
		// send 1st msg
		cipher= WPA2_encrypt(Nonce,tk,dict[0]);
		memcpy(msg,cipher.c_str(),cipher.size());
		msg[cipher.size()]=0;
		write(fd[1], msg, strlen(msg));
		sleep(1);

		// send 2nd msg
		Nonce=digits[1];
		cipher= WPA2_encrypt(Nonce,tk,dict[0]);
		memcpy(msg,cipher.c_str(),cipher.size());
		msg[cipher.size()]=0;
		write(fd[1], msg, strlen(msg));
		sleep(1);

		// send 3rd msg
		Nonce=digits[2];
		cipher= WPA2_encrypt(Nonce,tk,dict[0]);
		memcpy(msg,cipher.c_str(),cipher.size());
		msg[cipher.size()]=0;
		write(fd[1], msg, strlen(msg));
		sleep(1);

		// send 4th msg
		// key reinstallatiom
		Nonce=digits[0];
		cipher= WPA2_encrypt(Nonce,tk,dict[2]);
		memcpy(msg,cipher.c_str(),cipher.size());
		msg[cipher.size()]=0;
		write(fd[1], msg, strlen(msg));
		sleep(1);

		int status;
        wait(&status);
	}
	else  
	{	
		int		n2;
		int		fd2[2];
		pid_t	pid2;
		char	line2[MAXLINE];

		if (pipe(fd2) < 0) printf("pipe error");
	    if ((pid2 = fork()) < 0) printf("fork error");
		
	else if (pid2 > 0)	// Adversary
	{		
		char buf_adv[4096]={0};
		char msg_adv[4096]={0};
		close(fd2[0]);
		// recv 1st msg
		read(fd[0],buf_adv,1024);
		cout<<"adversary recv: "<<buf_adv<<endl;
		string M1(buf_adv);
		// recv 2nd msg
		read(fd[0],buf_adv,1024);
		cout<<"adversary recv: "<<buf_adv<<endl;
		// recv 3rd msg
		read(fd[0],buf_adv,1024);
		cout<<"adversary recv: "<<buf_adv<<endl;
		// recv 4th msg
		read(fd[0],buf_adv,1024);
		cout<<"adversary recv: "<<buf_adv<<endl;
		string M4(buf_adv);

		cout<<"M1 size="<<M1.size()<<endl;
		cout<<"M1"<<M1<<endl;
		cout<<"M4 size="<<M4.size()<<endl;
		cout<<"M4"<<M4<<endl;

		string mmn;
		for(int i=0;i<32;++i)
		{
			mmn+=int2char( char2int(M1[i])^char2int(M4[i]) );
		}
		cout<<mmn<<endl;


		
		for(int i=0;i<5;++i)
		{
			for(int j=i+1;j<5;++j)
			{
				cout<<dict[i]<<"^"<<dict[j]<<":"<<endl;
				string xmm;
				{
					for(int l=0;l<6;++l)
					{
						for(int k=0;k<6;++k)
						{
							char c1=dict[i].size()>l?dict[i][l]:0;
							char c2=dict[j].size()>k?dict[j][k]:0;
							int mn=(int)c1^int(c2);
							xmm+=int2char(mn/16);
							xmm+=int2char(mn%16);
						}
					}
				}
				cout<<xmm<<endl;
			}
		}
		

		

		int status;
		wait(&status);
	}
	else	// server
	{
		char buf_server[4096]={0};
		char msg_server[4096]={0};
		int r=0;
	}

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
    if(text.size()%32)
    {
        int pr=32 - (text.size()%32);
        std::string padding(pr,'0');
        text+=padding;
    }
    
    if(text.size()%32)
    {
        std::cout<<"padding error"<<std::endl;
        throw 1;
    }
    
	
	cout<<str<<endl;
	cout<<text<<endl;

    for(int i=0;i<text.size();++i)
	{
		int ab=(int)str[i%32] ^ (int)(text[i]);
		fine+=int2char(ab/16);
		fine+=int2char(ab%16);
		
	}
	
	
	
	
    
    return fine;

    
}