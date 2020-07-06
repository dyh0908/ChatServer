自己写的一个高并发服务器，正在进行中<br>
编写服务器的过程中主要参考了陈硕的《C++多线程服务器编程》
看完muduo网络库的我在仰望大佬的同时，深深的感觉到了与大佬的差距，怒从零写一个server！！！！希望可以在在了解muduo库主要功能的同时对其进行灵活使用<br>

项目名称 ：ChatServer
-----

可以工作在nginx tcp负载均衡环境中的集群聊天服务器和客户端源码,基于muduo网络库实现服务端的高并发、高性能，通过nginx进行负载均衡模块设计，通过redis缓存实现跨服务器通信，
实现了高性能、高并发、多服务器的聊天项目。

开发环境 ：
-------

本人使用的开发环境是ubuntu 20.04，使用了最新版的VSCode使得在windows系统下通过VSCode中的ssh插件<br>
远程连接到linux进行方便的开发和构建cmake。<br>
如果需要用到项目资源，只需要在ubuntu 20以上的版本中编译源码即可 <br>
可以使用autobuild.sh一键编译，也可以通过下面的编译命令：<br>
cd ./build <br>
cmake .. <br>
make <br>
CMakeLists.txt 文件都是编译好的，直接在build目录下进行cmake，得到makefile等一些中间文件，直接执行make命令即可。<br>

**客户端使用示例：**<br>
```
./client 127.0.0.1 6000
```
**服务端使用示例：**<br>
```
./server
```


文件详解：
--------
`/bin`                                                             ：用于生成可执行文件的文件夹，其中包含了生成的client和server。


`/src`  :  包含全部的源文件，分为client和server两大类。


`/thirdparty` :  包含了用到的三方库（这里包含了json.hpp）的文件。


`/include`    :  放置头文件的文件夹，包含了server文件夹和public.hpp —— 因为client客户端的实现简单，所以只在源文件的client中编写了，没有client的头文件。
public.hpp定义了消息的类型，server文件夹下存放的例如chatservice.hpp的头文件，注意server和service的文件不同，server是指整个服务器项目，service是指服务端。
                   
                   
`/build`      :  编译cmake的过程中生成的中间文件，为了提高文件的可读性，查阅方便，将cmake编译后生成的中间文件放
                   到了build里，Makefile同样也在这里面，所以cmake后直接在/build里执行make命令就可以了。
                   
`/autobuild.sh` : 写了一个简单的脚本以便自动化运行，也可以根据上面的编译方法手动编译。

内容详解：
-------
**版本1.0**<br>

`介绍：` 基于TCP的socket完成了简单的服务器和客户端的连接，实现了客户端向服务端发送数据服务端直接将数据打印出来的功能，主要是为测试服务端和客户端的通信，实现基于
socket的网络编程：包括socket、bind、listen、connection等函数的使用。<br>

`服务端的实现：`

```
#define MAXLINE 4096
int main(int argc,char**argv)
{
    int listenfd,connfd;
    struct sockaddr_in servaddr;  // 结构体，封装了ip + port + 协议
    char buff[4096];
    int n;

    //创建socket ， listenfd 唯一标识一个socket，
    //创建失败
    if((listenfd=socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
        printf("create socket error: %s(error:%d)\n",strerror(errno),errno);
        return 0;
    }    // 程序走到这代表创建成功
    
    // 清理功能，将servaddr每个都变成0
    memset(&servaddr,0,sizeof(servaddr));
    
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
        // 从套接字接收数据、接收套接字为connfd
        // 接收失败
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
```
**总结一下阻塞型服务端的基本套接字编程：** <br>
```
1：创建相应类型的套接字 ——> 2: 将套接字绑定相应端口号、IP地址、IP协议三元组 ——> 3: 监听端口号，相当于端口可用，开启服务 <br>
4: accept收到连接请求，建立连接 ——> 5: recv接收数据，将序列化好的数据放到buff里。
