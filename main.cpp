#include<iostream>
#include"header/server.h"
#include<thread>
using namespace std;
int main(){
    std::cout<<"START SERVER SERENA\n";

    Server serv(9998);
    std::thread th(&Server::StartProc,&serv);
    th.detach();
    cin.get();
    std::cout<<"SEND SERENA START\n";
    serv.SPAMSerSTART(1);
    cin.get();
    std::cout<<"SEND SERENA END\n";
    serv.SPAMSerSTOP(1);
    cin.get();
    return 0;
}