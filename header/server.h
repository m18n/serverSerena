#pragma once
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include<string.h>
#include<vector>
using namespace std;
void recV(int sock,char* buf,int size);
void senD(int sock,const char* buf,int size);
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
        while (1)
        {
            int sock = accept(listener, NULL, NULL);
            if (sock < 0)
            {
                perror("accept");
                exit(3);
            }

            std::cout<<"CONNECTCLIENT\n";
            char buff[20];
            recV(sock,buff,20);
            close(sock);
        }
    }

private:
    int listener;
};