#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <openssl/bn.h>
 
std::string genRand (int bits,int top,int bottom)
{
	BIGNUM *rnd;
	rnd = BN_new();
	char * result;
	BN_rand(rnd,bits,top,bottom);
	result = BN_bn2hex(rnd);	
	BN_free(rnd);
	return std::string(result);
}

