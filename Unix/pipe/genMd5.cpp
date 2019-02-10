#include<openssl/md5.h>
#include<openssl/sha.h>
#include<openssl/rsa.h>
#include <openssl/rand.h>
#include <openssl/bn.h>
#include<stdlib.h>
#include<stdio.h>
#include <string>
#include<string.h>
#include<math.h>


std::string genMd5(std::string plt)
{
  unsigned char* plaintext=new unsigned char[plt.size()+1];
  memcpy(plaintext,plt.c_str(),plt.size());
  plaintext[plt.size()]=0;
  unsigned char digest[MD5_DIGEST_LENGTH];
  MD5(plaintext, plt.size(), (unsigned char*)&digest);    
  char M1[300]={0};
  int i;
  for(i = 0; i < 16; i++)
  sprintf(&M1[i*2], "%02x", (unsigned int)digest[i]);

 return std::string(M1);
}



