#pragma once
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include<mutex>
using namespace std;
int recV(int sock, char *buf, int size);
int senD(int sock, const char *buf, int size);
struct client
{
    int socket;
    int city;
    bool conn = false;
};

class Server
{
private:
    void InitilServer(int port)
    {

        struct sockaddr_in addr;
        char buf[1024];
        int bytes_read;
        listener = socket(AF_INET, SOCK_STREAM, 0);
        if (listener < 0)
        {
            std::cout << "ERRRO SErVER\n";
            exit(1);
        }
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        if (bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        {
            perror("bind");
            exit(2);
        }

        listen(listener, 1);
        clients.resize(50);
    }
    int SearchIndex()
    {
        for (int i = 0; i < clients.size(); i++)
        {
            if (clients[i].conn == false)
                return i;
        }
    }

public:
    Server()
    {
        InitilServer(9999);
    }
    Server(int port)
    {
        InitilServer(port);
    }
    void StartProc()
    {
        char city[20];
        mutex mt;
        while (1)
        {
            int sock = accept(listener, NULL, NULL);
            if (sock < 0)
            {
                perror("accept");
                exit(3);
            }
            
            
            std::cout << "CONNECTCLIENT\n";
            int index = SearchIndex();
            recV(sock, city, 20);
            
            this->clients[index].conn = true;
            this->clients[index].socket = sock;
            this->clients[index].city = atoi(city);
            std::cout<< "CITY " << this->clients[index].city << "\n";
            std::cout<<"ADRESS"<<&this->clients<<"\n";
        }
    }
    void SPAMSerSTART(int city)
    {
         std::cout<<"ADRESS"<<&this->clients<<"\n";
        for (int i = 0; i < this->clients.size(); i++)
        {
            if (this->clients[i].conn == true)
            {
                senD(this->clients[i].socket, "START", 6);
            }
        }
    }
    void SPAMSerSTOP(int city)
    {
        for (int i = 0; i < clients.size(); i++)
        {
            if (clients[i].conn == true)
            {
                senD(clients[i].socket, "STOP", 6);
            }
        }
    }
    ~Server(){
        std::cout<<"DISTRUCK\n";
        for(int i=0;i<clients.size();i++){
            if(clients[i].conn==true){
                close(clients[i].socket);
            }
        }
    }
private:
    std::vector<client> clients;
    int listener;
};