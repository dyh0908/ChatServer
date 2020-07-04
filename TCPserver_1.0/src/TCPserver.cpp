/*
TCPserver 1.0 ———— server
writer: by Deng Yaohui
Date: 2020 03 01 
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>


#define MAXLINE 4096

int main(int argc,char**argv)
{
    int listenfd,connfd;
    struct sockaddr_in servaddr;  // 结构体，封装了ip+port+协议
    char buff[4096];
    int n;

    //创建socket ， listenfd 唯一标识一个socket，
    //失败
    if((listenfd=socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
        printf("create socket error: %s(error:%d)\n",strerror(errno),errno);
        return 0;
    }
    
    memset(&servaddr,0,sizeof(servaddr)); // 清理功能，将servaddr每个都变成0。
    // 为结构体初始化
    servaddr.sin_family=AF_INET;   // IPV4
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);  // 表示本服务器的任意IP地址，有时候一台机器有多个ip地址
    servaddr.sin_port=htons(6666);

    // 绑定三元组 ，监听socket描述字为listenfd
    if(bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr))==-1)
    {
        printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
        return 0;
    }
    
    // listen 监听端口号，等待客户连接
    if(listen(listenfd,10)==-1)
    {
        printf("listen socket error: %s(errno:%d)\n",strerror(errno),errno);
        return 0;
    }
    printf("======waiting for client's request=======\n");
    
    while(1)
    {
        // 从套接字接收数据、接收套接字为connfd  接受失败
        if((connfd=accept(listenfd,(struct sockaddr*)NULL,NULL))==-1)
        {
           printf("accept socket error: %s(errno:%d)\n",strerror(errno),errno);
           continue;
        }
        // 接收成功
        // n为接收数据的大小
        n= recv(connfd,buff,MAXLINE,0); // 接收到buf里面，但是recv不会主动给buf添加结束符'\0'
        buff[n]='\0';  // 手动添加结束符
        printf("recv msg from client: %s\n",buff); //将接收的信息打印出来
        close(connfd);
    }
    close(listenfd);
    return 0;
}