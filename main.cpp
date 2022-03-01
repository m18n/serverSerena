#include<iostream>
#include"header/server.h"
using namespace std;
int main(){
    std::cout<<"START SERVER SERENA\n";

    Server serv(9998);
    serv.StartProc();
    cin.get();
    cin.get();
    return 0;
}