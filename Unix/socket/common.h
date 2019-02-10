#include <string>

enum RetCode {Ret_Success=0,Ret_Error};
std::string genRand (int bits,int top,int bottom);
std::string Wap2CliendRecv(std::string ip,std::string port);
int Wap2CliendSend(std::string ip,std::string port,const char* bytes);
