
#include <iostream>
#include <thread>
#include <chrono>
#include <unistd.h>
using namespace std;
int main( )
{
    setvbuf(stdout, NULL, _IONBF, 0);
     setvbuf(stdin, NULL, _IONBF, 0);
    thread([]{
    while(1){
    this_thread::sleep_for(chrono::seconds(1));
    printf( " 1" );
    }
    }).detach();
    while(1){
    printf("2");
    int  a;
    cin >> a;
    printf("%d", a);
    }
    return 0;
}
