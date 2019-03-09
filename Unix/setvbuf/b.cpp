
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
int main( )
{
    thread([]{
    while(1){
    this_thread::sleep_for(chrono::seconds(1));
    printf( " 1\n" );
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
