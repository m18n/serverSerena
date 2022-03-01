#include"header/server.h"
void recV(int sock,char* buf,int size){
    int len=recv(sock,buf,size,MSG_PEEK);
    
    int indexs=0;
    for(int i=0;i<len;i++){
        if(buf[i]==':'){
            indexs=i;
            break;
        }
    }
    char strsize[10];
    recv(sock,strsize,indexs+1,NULL);
    strsize[indexs]='\0';
    int realsize=atoi(strsize);
    recv(sock,buf,realsize,NULL);
   
}
void senD(int sock,const char* buf,int size){
    static std::vector<char> vec(500);
    std::string sizestr=std::to_string(size);
    int indexs=sizestr.length();
    memcpy(&vec[0],&sizestr[0],indexs);
    vec[indexs]=':';
    memcpy(&vec[indexs+1],&buf[0],size);
    int allsize=indexs+size+2;
    vec[allsize-1]='\0';
    send(sock,&vec[0],allsize,NULL);
}